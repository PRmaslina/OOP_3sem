#include "server.h"

Server::Server(QObject *parent)
    : QObject(parent)
    , m_udpSocket(nullptr)
    , m_port(0)
    , m_isRunning(false)
{
}

Server::~Server()
{
    stopServer();
}

bool Server::startServer(quint16 port)
{
    if (m_isRunning) {
        qWarning() << "Server is already running";
        return false;
    }

    m_udpSocket = new QUdpSocket(this);
    m_port = port;

    if (!m_udpSocket->bind(QHostAddress::Any, port)) {
        qCritical() << "Failed to bind to port" << port;
        delete m_udpSocket;
        m_udpSocket = nullptr;
        return false;
    }

    connect(m_udpSocket, &QUdpSocket::readyRead,
            this, &Server::readPendingDatagrams);

    m_isRunning = true;
    qInfo() << "UDP Server started on port" << port;

    return true;
}

void Server::stopServer()
{
    if (m_udpSocket) {
        m_udpSocket->close();
        m_udpSocket->deleteLater();
        m_udpSocket = nullptr;
    }

    m_isRunning = false;
    qInfo() << "UDP Server stopped";
}

void Server::readPendingDatagrams()
{
    if (!m_udpSocket) return;

    while (m_udpSocket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = m_udpSocket->receiveDatagram();
        if (datagram.isValid()) {
            processDatagram(datagram);
        }
    }
}

void Server::processDatagram(const QNetworkDatagram &datagram)
{
    QByteArray data = datagram.data();
    QHostAddress senderAddress = datagram.senderAddress();
    quint16 senderPort = datagram.senderPort();

    qDebug() << "Received message from" << senderAddress.toString()
             << ":" << senderPort << "-" << data;

    // Обрабатываем сообщение и получаем ответ
    QByteArray response = processMessage(data, senderAddress, senderPort);

    // Отправляем ответ
    if (!response.isEmpty()) {
        qint64 bytesSent = m_udpSocket->writeDatagram(response, senderAddress, senderPort);

        if (bytesSent == -1) {
            qWarning() << "Failed to send response to" << senderAddress.toString() << ":" << senderPort;
        } else {
            qDebug() << "Sent response to" << senderAddress.toString() << ":" << senderPort
                     << "-" << response;
        }
    }
}

QByteArray Server::processMessage(const QByteArray &data, const QHostAddress &sender, quint16 senderPort)
{
    QString message = QString::fromUtf8(data).trimmed();
    QString response;
    QChar command = message[0];
    message[0] = ' ';
    // Обработка различных команд
    if (command == '1' ) {
        p.setPrintType(1);
        response = outputString(p);
    }
    else if (command == '2' ){
        p.setPrintType(2);
        response = outputString(p);
    }
    else if (command == '3'  ) {
        QString A;
        for(int i = 1; message[i] != ' '; i++,message[i] = ' '){
            A+=message[i];
        }
        inputString(A,message,&p);
        response = outputString(p);
    }
    else if (command == '4'  ){
        response = QString("Hello from server! Your address: %1:%2")
        .arg(sender.toString())
            .arg(senderPort);
    }
    else if (command == '5'  ) {
        number a = p.solve(toComplex(message));
        response = "значение в точке " + message + "  равно: " + complexOut(a);
    }

    return response.toUtf8();
}
