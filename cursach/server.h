#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <QDebug>
#include <QTime>
#include <QByteArray>
#include <QUdpSocket>
#include <QDebug>

#include "message.h"
#include "session.h"
#include "playerlistitem.h"

class Server : public QObject
{
    Q_OBJECT
private:
    QVector<QTcpSocket*> Sockets;
    QVector<Player*> Players;
    QByteArray Data;
    Session session;
    quint16 nextBlockSize = 0;
    bool isRunning = 0;
    void SendToClient(QTcpSocket* socket, MessageType type, QString message = "");
    void SendToAll(MessageType, QString);
    
    void processMessage(QTcpSocket*, MessageType, QString);
    void processDatagram(QNetworkDatagram);
    QTimer* timer;
    int remainingTime = 10000;
    int timeStep = 1000;
public:
    explicit Server(QObject *parent = nullptr);
    ~Server();

    QTcpServer *server;
    QUdpSocket *udpSocket;
    int startServer(quint16 port);
    int stopServer();
    QHostAddress getIp();

    QHostAddress getLocalIp();
    quint16 getPort();
    void startCountdown(int startingTime, int step = 1000);
    void stopCountdown();
private slots:
    void updateCountdown();
public slots:
    void newConnection();
    void readyRead();
    void readPendingDatagrams();
    void disconected();
};
#endif // SERVER_H
