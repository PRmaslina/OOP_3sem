#include "client.h"

#include <QTimer>
#include "message.h"
#include "playerlistitem.h"
#include "serverlistitem.h"
#include "app.h"
#include "ui_app.h"


Client::Client(QObject *parent)
    : QObject{parent}, m_port(0) {
    tcpSocket = new QTcpSocket(this);
    udpSocket = new QUdpSocket(this);
    nextBlockSize = 0;
    this->parent = parent;
    player = {0, "Player0", 0};
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    udpSocket->bind(QHostAddress::Any, m_port);
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
}

Client::~Client() {

}

bool Client::connectToServer(QHostAddress ip, quint16 port) {
    tcpSocket->connectToHost(ip, port);
    if (tcpSocket->waitForConnected(3000)) {
        qDebug() << "[Client] connected to" << ip.toString() << port;
        qDebug() << "[Client] state:" << tcpSocket->state();

        return tcpSocket->isValid() && tcpSocket->isWritable();
    }
    return 0;
}

void Client::disconnectFromServer() {
    if (m_isHost) SendToServer(MessageType::StopServer, "");
    else tcpSocket->disconnectFromHost();
}

void Client::SendToServer(MessageType type, QString message) {
    qDebug() << "[Client] sending message:" << type << message;
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_2);
    out << quint16(0) << type << message;
    out.device()->seek(0);
    qDebug() << "[Client] DataSize: " << quint16(Data.size() - sizeof(quint16));
    out << quint16(Data.size() - sizeof(quint16));
    qint16 bytes = tcpSocket->write(Data);
    if (bytes == -1)
        qDebug() << "[Client] Write error:" << tcpSocket->errorString();
    else {
        qDebug() << "[Client] Message sent to " << tcpSocket->peerAddress().toString() << tcpSocket->peerPort();
        tcpSocket->flush();
    }
}

void Client::CallForServers(quint16 port, Session session) {
    Sessions.clear();
    QString message = "{" + QString::number(MessageType::AnyoneThere) + "}" +
                      QString::number(session.hasPassword) + ":" +
                      QString::number(session.boardSize);
    QByteArray dgram = message.toUtf8();
    udpSocket->writeDatagram(dgram, QHostAddress::Broadcast, port);
}

void Client::updatePlayer(Player update, bool sendToServer) {
    update.id = player.id;
    player = update;
    QString message = QString::number(player.id) + ":" +
                      player.name + ":" +
                      QString::number(player.ready);
    if (sendToServer) SendToServer(MessageType::PlayerInfo, message);
}

void Client::updateSession(Session update, bool sendToServer) {
    thisSession = update;
    QString message = thisSession.name + ":" +
                      QString::number(thisSession.hasPassword) + ":" +
                      thisSession.password + ":" +
                      QString::number(thisSession.boardSize);
    if (sendToServer) SendToServer(MessageType::SessionInfo, message);
}

void Client::setIsHost(bool isHost) {
    m_isHost = isHost;
}

void Client::setPendingSession(Session session) {
    m_pendingSessionUpdate = session;
    thisSession = session;
}

void Client::setSession(Session *session) {
    thisSession = *session;
}

void Client::updateMove(int x, int y) {
    QString message = QString("%1:%2:%3").arg(player.id).arg(x).arg(y);
    SendToServer(MessageType::Move, message);
}

void Client::updateBoard(QVector<BoardTile *> board) {
    QString message = QString("%1,").arg(player.id);
    for (auto tile : board) {
        message += QString("%1:%2:%3,").arg(tile->getX()).arg(tile->getY()).arg(tile->getValue());
    }
    message.removeAt(message.size() - 1);
    SendToServer(MessageType::Board, message);
}

void Client::processDatagram(QNetworkDatagram datagram) {
    QString data = QString::fromUtf8(datagram.data()).trimmed();
    qDebug() << "[Client] received: " << data;
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

    auto UI = ((App*)parent)->ui;
    MessageType type = MessageType(command.toInt());
    switch (type) {
    case MessageType::HereWeR: {
        qDebug() << "[Client] HereWeR";
        Session* newSession = new Session;
        auto temp = data.split(':');
        newSession->serverAddress = QHostAddress(temp[0]);
        newSession->serverPort = temp[1].toInt();
        newSession->name = temp[2];
        newSession->hasPassword = temp[3].toInt();
        newSession->boardSize = temp[4].toInt();
        newSession->playersAmount = temp[5].toInt();
        Sessions.append(newSession);
        serverListItem* item = new serverListItem;
        item->session = newSession;
        item->updateThis();
        UI->serverList->addWidget(item);
        connect(item, &serverListItem::clicked, (App*)parent, &App::changeSelecion);
        break;
    }
    default:
        break;
    }
}

void Client::processMessage(MessageType type, QString message) {
    qDebug() << "[Client] received: " << type << message;
    auto UI = ((App*)parent)->ui;
    switch (type) {
    case MessageType::PlayerInfo: {
        qDebug() << "[Client] PlayerInfo";
        int id = message.toInt();
        player.id = id;
        player.name = UI->playerNameLEdit->text();
        QString name = player.name;
        bool ready = player.ready;
        QString msg = QString::number(id) + ":" + name + ":" + QString::number(ready);
        SendToServer(MessageType::PlayerInfo, msg);

    } break;
    case MessageType::UpdatePLayers: {
        qDebug() << "[Client] UpdatePlayers";
        clearLayout(UI->playerList);
        clearLayout(UI->playerList_2);
        int i = 0;
        for (auto player : message.split(',')) {
            auto temp = player.split(':');
            QString name = temp[0];
            bool ready = temp[1].toInt();
            PlayerListItem* p0 = new PlayerListItem;
            p0->player = new Player{0, name, ready};
            p0->updateItem();
            UI->playerList->addWidget(p0);
            PlayerListItem* p1 = new PlayerListItem;
            p1->player = new Player;
            *(p1->player) = *(p0->player);
            p1->updateItem();
            UI->playerList_2->addWidget(p1);
            if (this->player.id == i) {
                p1->mark();
                UI->myName->setText(p1->player->name);
            } else {
                UI->enemyName->setText(p1->player->name);
            }
            if (this->player.id == i) p0->mark();
            i++;
        }
        if (thisSession.gameState > 0 && i < thisSession.maxPlayers) {
            thisSession.gameState = 0;
            player.tiles.clear();
            ((App*)parent)->finishGame();
        }

        if (m_isHost && !m_pendingSessionUpdate.name.isEmpty()) {
            thisSession = m_pendingSessionUpdate;
            QString sessionMsg = thisSession.name + ":" +
                                 QString::number(thisSession.hasPassword) + ":" +
                                 thisSession.password + ":" +
                                 QString::number(thisSession.boardSize);
            SendToServer(MessageType::SessionInfo, sessionMsg);
            m_pendingSessionUpdate = {}; // Очищаем
        }

        if (UI->stackedWidget->currentWidget() != UI->waitPage && thisSession.gameState == 0) UI->stackedWidget->setCurrentWidget(UI->waitPage);
    } break;
    case MessageType::SessionInfo: {
        qDebug() << "[Client] SessionInfo";
        auto temp = message.split(':');
        thisSession.name = temp[0];
        thisSession.playersAmount = temp[1].toInt();
        UI->gameNameLabel->setText(thisSession.name);
    } break;
    case MessageType::AnyoneThere: {
        qDebug() << "[Client] AnyoneThere";
        if (message == "bye") {
            tcpSocket->disconnectFromHost();
            UI->gameNameLabel->text() = "";
            auto* layout = UI->playerList;
            clearLayout(layout);
            ((App*)parent)->playerReady = false;
            UI->readyButton->setText("Ready");
            UI->stackedWidget->setCurrentWidget(UI->menuPage);
        }
    } break;
    case MessageType::Auth: {
        qDebug() << "[Client] Auth";
        SendToServer(MessageType::Auth, password);
    } break;
    case MessageType::AuthStatus: {
        qDebug() << "[Client] AuthStatus";
        if (!message.toInt()) {
            qDebug() << "[Client] Auth status: 0";
            tcpSocket->disconnectFromHost();
            ((App*)parent)->messageBox("Wrong password!");
            break;
        }
        qDebug() << "[Client] Auth status 1";

    } break;
    case MessageType::StartGame: {
        qDebug() << "[Client] StartGame";
        switch(message.split(':')[0].toInt()) {
        case 0: {
            ((App*)parent)->stopCountdown();
            thisSession.gameState = 0;
        } break;
        case 1: {
            ((App*)parent)->startCountdown(5000, 300);
            thisSession.gameState = 1;
        } break;
        case 2: {
            ((App*)parent)->startPreparation(thisSession.boardSize);
            thisSession.gameState = 2;
        } break;
        case 3: {
            thisSession.movesAmount = message.split(':')[1].toInt() + 1;
            ((App*)parent)->startGame(thisSession.movesAmount);
            thisSession.gameState = 3;
        }
        default:
            break;
        }
    } break;
    case MessageType::Move: {
        qDebug() << "[Client] Move";
        auto temp = message.split(':');
        qDebug() << "[Client]" << temp[0];
        if (temp.size() >= 4) {
            if (player.move <= temp[0].toInt()) ((App*)parent)->setEnemyMove(temp[1].toInt(), temp[2].toInt(), temp[3].toInt());
            if (player.move) ((App*)parent)->setMyMove(temp[1].toInt(), temp[2].toInt(), temp[3].toInt());
        }
        ((App*)parent)->updateMoves(temp[0].toInt());
    } break;
    case MessageType::FinishGame: {
        qDebug() << "[Client] FinishGame";
        switch(message.toInt()) {
        case 0: {
            ((App*)parent)->messageBox("You lose!");
        } break;
        case 1: {
            ((App*)parent)->messageBox("You win!");
        } break;
        case 2: {
            ((App*)parent)->messageBox("Friendship wins!");
        } break;
        default:
            break;
        }
        thisSession.gameState = 0;
        player.tiles.clear();
        ((App*)parent)->finishGame();
    } break;
    default:
        qDebug() << "[Client] Unknown message type";
        break;
    }
}

void Client::clearLayout(QLayout* layout) {
    QLayoutItem* item;
    while ((item = layout->takeAt(0)) != nullptr) {
        if (item->widget()) {
            item->widget()->deleteLater();
        }
        delete item;
    }
}

void Client::readyRead() {
    qDebug() << "[Client] TCP got a message!";
    QTcpSocket* socket = (QTcpSocket*)sender();
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_2); // Установите версию!

    // Читаем все доступные данные
    while (socket->bytesAvailable() > 0) {
        if (nextBlockSize == 0) {
            if (socket->bytesAvailable() < sizeof(quint16)) {
                qDebug() << "[Client] not enough data";
                return;
            }
            in >> nextBlockSize;
            qDebug() << "[Client] nextBlockSize =" << nextBlockSize;
        }

        if (socket->bytesAvailable() < nextBlockSize) {
            // Не все данные блока пришли
            qDebug() << "[Client] Waiting for more data. Have:" << socket->bytesAvailable()
                     << "Need:" << nextBlockSize;
            return;
        }

        // Читаем полный блок
        MessageType type;
        QString message;
        in >> type >> message;

        qDebug() << "[Client] Full message received. Type:" << type << "Message:" << message;
        processMessage(type, message);

        // Сбрасываем размер для следующего блока
        nextBlockSize = 0;
    }
}

void Client::readPendingDatagrams() {
    qDebug() << "[Client] UDP got a message!";
    while(udpSocket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = udpSocket->receiveDatagram();
        if (datagram.isValid()) {
            processDatagram(datagram);
        }
    }
}
