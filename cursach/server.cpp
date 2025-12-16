#include "server.h"

#include <QNetworkDatagram>
#include <QNetworkInterface>
#include <QTimer>
#include "message.h"
#include "session.h"

Server::Server(QObject *parent)
    : QObject{parent} {
    server = new QTcpServer(this);
    udpSocket = new QUdpSocket(this);
    timer = new QTimer;
    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
    connect(timer, &QTimer::timeout, this, &Server::updateCountdown);
}

Server::~Server() {
    delete server;
    delete udpSocket;
    delete timer;
}

int Server::startServer(quint16 port) {
    isRunning = server->listen(QHostAddress::Any, 0);
    udpSocket->bind(port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    if (isRunning)
        qDebug() << "[Server] started at" << server->serverAddress() << ":" << server->serverPort();
    else
        qDebug() << "[Server] not started";
    session = {getLocalIp(), port, "", 0, "", 0, 0};
    return isRunning;
}

int Server::stopServer()
{
    for (auto socket : Sockets) {
        SendToClient(socket, MessageType::AnyoneThere, "bye");
    }
    Sockets.clear();
    Players.clear();
    server->close();
    udpSocket->close();
    isRunning = false;
    qDebug() << "[Server] stopped";
    return 0;
}

QHostAddress Server::getIp() {
    if (!isRunning) return QHostAddress("0.0.0.0");
    return server->serverAddress();
}

QHostAddress Server::getLocalIp() {
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();

    for (const QHostAddress &address : ipAddressesList) {
        // Пропускаем локальные адреса и IPv6
        if (address.protocol() == QAbstractSocket::IPv4Protocol &&
            address != QHostAddress(QHostAddress::LocalHost)) {
            // Проверяем, что это не частный адрес (или проверяем конкретный диапазон)
            if (address.toString().startsWith("192.168.") ||
                address.toString().startsWith("10.") ||
                address.toString().startsWith("172.")) {
                return address;
            }
        }
    }

    // Если не нашли, возвращаем localhost
    return QHostAddress(QHostAddress::LocalHost);
}

quint16 Server::getPort() {
    if (!isRunning) return 0;
    return server->serverPort();
}

void Server::startCountdown(int startingTime, int step) {
    remainingTime = startingTime;
    timeStep = step;
    timer->start(step);
}

void Server::stopCountdown() {
    timer->stop();
}

void Server::updateCountdown() {
    remainingTime -= timeStep;
    if (remainingTime <= 0) {
        timer->stop();
        bool startGame = session.maxPlayers == Players.size();
        for (auto player : Players) {
            startGame = startGame && player->ready;
        }
        if (startGame) {
            SendToAll(MessageType::StartGame, "2");
            session.gameState = 1;
        }
    }
}

void Server::readPendingDatagrams() {
    while(udpSocket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = udpSocket->receiveDatagram();
        if (datagram.isValid()) {
            processDatagram(datagram);
        }
    }
}

void Server::newConnection() {
    if (!(Sockets.size() < session.maxPlayers)) return;
    QTcpSocket *socket = server->nextPendingConnection();
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconected()));
    socket->setSocketOption(QAbstractSocket::LowDelayOption, 1);
    socket->setSocketOption(QAbstractSocket::KeepAliveOption, 1);
    Sockets.append(socket);
    qDebug() << "[Server] new client connected from" << socket->peerAddress().toString();
    //if (Sockets.size() == 1) SendToClient(socket, MessageType::SessionInfo);
    Player* p = new Player{(int)Players.size(), "", 0};
    Players.append(p);
    session.playersAmount = Players.size();
    QTimer::singleShot(0, [this, socket, p]() {
        if (socket->state() == QAbstractSocket::ConnectedState) {
            if (Sockets.size() > 0 && session.hasPassword) SendToClient(socket, MessageType::Auth, "0");
            else SendToClient(socket, MessageType::PlayerInfo, QString::number(p->id));
        }
    });
}

void Server::readyRead() {
    QTcpSocket* socket = (QTcpSocket*)sender();
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_2); // Установите версию!

    // Читаем все доступные данные
    while (socket->bytesAvailable() > 0) {
        if (nextBlockSize == 0) {
            if (socket->bytesAvailable() < sizeof(quint16)) {
                qDebug() << "[Server] not enough data";
                return;
            }
            in >> nextBlockSize;
            qDebug() << "[Server] nextBlockSize =" << nextBlockSize;
        }

        if (socket->bytesAvailable() < nextBlockSize) {
            // Не все данные блока пришли
            qDebug() << "[Server] Waiting for more data. Have:" << socket->bytesAvailable()
                     << "Need:" << nextBlockSize;
            return;
        }

        // Читаем полный блок
        MessageType type;
        QString message;
        in >> type >> message;

        qDebug() << "[Server] Full message received. Type:" << type << "Message:" << message;
        processMessage(socket, type, message);

        // Сбрасываем размер для следующего блока
        nextBlockSize = 0;
    }
}

void Server::disconected() {
    QTcpSocket* socket = (QTcpSocket*)sender();
    for (int i = 0; i < Sockets.size(); i++) {
        if (Sockets[i] == socket) {
            Sockets.remove(i);
            Players.remove(i);
            break;
        }
    }
    socket->deleteLater();
    QString message = "";
    for (auto player : Players) {
        message += player->name + ":" + QString::number(player->ready) + ",";
    }
    message.removeAt(message.size() - 1);
    session.playersAmount = Players.size();
    session.gameState = 0;
    SendToAll(MessageType::UpdatePLayers, message);
}


void Server::SendToClient(QTcpSocket* socket, MessageType type, QString message) {
    qDebug() << "[Server] sending message:" << type << message;
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_2);
    out << quint16(0) << type << message;
    out.device()->seek(0);
    qDebug() << "[Server] DataSize: " << quint16(Data.size() - sizeof(quint16));
    out << quint16(Data.size() - sizeof(quint16));
    qint16 bytes;
    bytes = socket->write(Data);
    if (bytes == -1)
        qDebug() << "[Server] Write error:" << socket->errorString();
    else {
        qDebug() << "[Server] Message sent to " << socket->peerAddress().toString() << socket->peerPort();
        socket->flush();
    }
}

void Server::SendToAll(MessageType type, QString message) {
    for (auto socket : Sockets) {
        SendToClient(socket, type, message);
    }
}

void Server::processMessage(QTcpSocket* socket, MessageType type, QString message) {
    qDebug() << "[Server] received: " << type << message;
    switch (type) {
    case MessageType::PlayerInfo: {
        qDebug() << "[Server] PlayerInfo";
        auto temp = message.split(':');
        int id = temp[0].toInt();
        QString name = temp[1];
        bool ready = temp[2].toInt();
        Players[id]->name = name;
        Players[id]->ready = ready;
        bool startGame = session.maxPlayers == Players.size();
        QString message = "";
        for (auto player : Players) {
            message += player->name + ":" + QString::number(player->ready) + ",";
            startGame = startGame && player->ready;
        }
        message.removeAt(message.size() - 1);
        SendToAll(MessageType::UpdatePLayers, message);
        if (session.gameState == 0) {
            SendToAll(MessageType::SessionInfo, session.name + ":" + QString::number(session.playersAmount));
            if (Players.size() == session.maxPlayers) SendToAll(MessageType::StartGame, QString::number(startGame));
            if(startGame) startCountdown(5000, 1000);
            else stopCountdown();
        }
        else if (startGame && session.gameState == 1) {
            session.gameState = 2;
            session.movesAmount = pow(session.boardSize, 2) + (session.boardSize % 2);
            SendToAll(MessageType::StartGame, QString("3:%1").arg(session.movesAmount));
            for (int i = 0; i < Players.size(); i++) {
                QString newMessage = QString("%1").arg((session.move % Players.size() == i) ? 1 : 0);
                SendToClient(Sockets[i], MessageType::Move, newMessage);
            }
        }
    } break;
    case MessageType::SessionInfo: {
        qDebug() << "[Server] SessionInfo";
        auto temp = message.split(':');
        session = {session.serverAddress, session.serverPort, temp[0], (bool)temp[1].toInt(), temp[2], temp[3].toInt(), (int)Sockets.size()};
        SendToAll(MessageType::SessionInfo, session.name + ":" + QString::number(session.playersAmount));
    } break;
    case MessageType::StopServer: {
        qDebug() << "[Server] StopServer";
        stopServer();
    } break;
    case MessageType::Auth: {
        qDebug() << "[Server] Auth";
        if (session.password == message) {
            qDebug() << "[Server] auth completed";
            SendToClient(socket, MessageType::AuthStatus, "1");
            SendToClient(socket, MessageType::PlayerInfo, QString::number(Players.size() - 1));
        }
        else {
            qDebug() << "[Server] auth failed";
            SendToClient(socket, MessageType::AuthStatus, "0");
        }
    } break;
    case MessageType::Board: {
        qDebug() << "[Server] Board";
        auto tiles = message.split(',');
        int id = tiles[0].toInt();
        tiles.removeAt(0);
        for (auto tile : tiles) {
            auto temp = tile.split(':');
            Players[id]->tiles.append({temp[0].toInt(), temp[1].toInt(), temp[2].toInt()});
        }
    } break;
    case MessageType::Move: {
        qDebug() << "[Server] Move";
        session.move++;
        auto temp = message.split(':');
        int id = temp[0].toInt();
        int value = 0;
        for (auto tile : Players[(id + 1) % Players.size()]->tiles) {
            if (tile.x == temp[1].toInt() && tile.y == temp[2].toInt()) {
                value = tile.v;
                break;
            }
        }
        qDebug() << QString("[Server] %1 [%5]: (%2, %3) - %4").arg(Players[id]->name).arg(temp[1].toInt()).arg(temp[2].toInt()).arg(value).arg(id).toStdString();
        Players[id]->points += value;
        qDebug() << QString("[Server] %1 [%3]: %2").arg(Players[id]->name).arg(Players[id]->points).arg(id).toStdString();
        for (int i = 0; i < Players.size(); i++) {
            QString newMessage = QString("%1:%2:%3:%4").arg((session.move % Players.size() == i) ? 1 : 0).arg(temp[1]).arg(temp[2]).arg(value);
            SendToClient(Sockets[i], MessageType::Move, newMessage);
        }
        if (Players[id]->points == (session.boardSize * (session.boardSize + 1)) / 2 || session.move == session.movesAmount) {
            int winner = 0;
            bool friendshipWon = 1;
            for (int i = 1; i < Players.size(); i++) {
                if (Players[i]->points != Players[winner]->points) friendshipWon = 0;
                if (Players[i]->points > Players[winner]->points) winner = i;
            }
            if (friendshipWon) {
                qDebug() << "[Server] Friendship won!";
                SendToAll(MessageType::FinishGame, "2");
            }
            else {
                qDebug() << QString("[Server] %1 [%2]: wins!").arg(Players[winner]->name).arg(winner).toStdString();
                for (int i = 0; i < Sockets.size(); i++) {
                    if (i == winner) continue;
                    SendToClient(Sockets[i], MessageType::FinishGame, "0");
                }
                SendToClient(Sockets[winner], MessageType::FinishGame, "1");
            }
            session.gameState = 0;
            session.move = 0;
            session.movesAmount = 0;
            for (auto player : Players) {
                player->ready = 0;
                player->move = 0;
                player->points = 0;
                player->tiles.clear();
            }
        }
    } break;
    default:
        qDebug() << "[Server] Unknown message type";
        break;
    }
    message = " ";
}

void Server::processDatagram(QNetworkDatagram datagram) {
    QString data = QString::fromUtf8(datagram.data()).trimmed();
    QHostAddress senderAddress = datagram.senderAddress();
    quint16 senderPort = datagram.senderPort();

    QString command = "";

    for (int i = 0, k = 0; i < data.size() && k < 2; i++) {
        if (data[i] == '{' || data[i] == '}') k++;
        else if (k) {
            command += data[i];
        }
        data[i] = ' ';
    }
    data = data.trimmed();

    MessageType type = MessageType(command.toInt());
    switch (type) {
    case MessageType::AnyoneThere: {
        Session newSession{};
        auto temp = data.split(':');
        newSession.hasPassword = temp[0].toInt();
        newSession.boardSize = temp[1].toInt();
        QString message = "{" + QString::number(MessageType::HereWeR) + "}" +
                          getLocalIp().toString() + ":" +
                          QString::number(server->serverPort()) + ":" +
                          session.name + ":" +
                          QString::number(session.hasPassword) + ":" +
                          QString::number(session.boardSize) + ":" +
                          QString::number(session.playersAmount);
        QByteArray dgram = message.toUtf8();
        if (newSession.hasPassword >= session.hasPassword &&
            newSession.boardSize >= session.boardSize &&
            session.playersAmount < session.maxPlayers) udpSocket->writeDatagram(dgram, senderAddress, senderPort);
        break;
    }
    default:
        break;
    }
}



