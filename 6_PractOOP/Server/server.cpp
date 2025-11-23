#include "server.h"

Server::Server(QObject *parent)
    : QObject(parent)
    , m_udpSocket(nullptr)
    , m_port(4444)
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
    QByteArray response = processMessage(data);

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

QByteArray Server::processMessage(const QByteArray &data)
{
    QString message = QString::fromUtf8(data).trimmed();
    QString response;
    QString sessionId = "";

    // Извлекаем session ID
    for(int i = 0, k = 0; k < 2 && i < message.length() ;i++){
        if (k){
            sessionId += message[i];
        }
        if(message[i] == '{' || message[i] == '}'){
            k++;
        }
        message[i] = ' ';
    }
    message = message.trimmed();

    QChar command = message[0];
    message[0] = ' ';
    message = message.trimmed();

    Session* currentSession = nullptr;
    if(command != '5')
    {
        // Находим сессию
        if (sessionId.toInt() <= sessions.size()) {
            currentSession = sessions.data()[sessionId.toInt()];
        }

        if (!currentSession) {
            return "Invalid session";
        }
    }

    if (command == '1' ) {
        currentSession->setPrintType(1);
        response = "1" + currentSession->getOutputString();
    }
    else if (command == '2' ){
        currentSession->setPrintType(2);
        response = "2" + currentSession->getOutputString();
    }
    else if (command == '3'  ) {
        QString A;
        for(int i = 0; i < message.length() && message[i] != ' '; i++){
            A += message[i];
            message[i] = ' ';
        }
        message = message.trimmed();
        currentSession->updatePolynom(A, message);
        response = "3" + currentSession->getOutputString();
    }
    else if (command == '4'  ) {
        QString result = currentSession->solveAtPoint(message);
        response = "4Значение в точке " + message + " равно: " + result;
    }
    else if (command == '5'  ) {
        // Создаем сессию по умолчанию с вещественными числами
        QString newSessionId = "{" + QString::number(sessions.size() + 1) + "}";
        Session* newSession = new Session(newSessionId, REAL_NUMBERS);
        sessions.push_back(newSession);
        response = "2" + newSessionId;
    }
    else if (command == '6' ) {
        // Смена типа чисел
        bool useComplex = (message == "1");
        NumberType newType = useComplex ? COMPLEX_NUMBERS : REAL_NUMBERS;

        // Создаем новую сессию с нужным типом
        Session* newSession = new Session(currentSession->id, newType);

        // Заменяем старую сессию
        for (int i = 0; i < sessions.size(); i++) {
            if (sessions[i]->id == currentSession->id) {
                delete sessions[i];
                sessions[i] = newSession;
                break;
            }
        }

        response = "6Тип чисел изменен на: " + QString(useComplex ? "комплексные" : "вещественные");
    }

    return response.toUtf8();
}
