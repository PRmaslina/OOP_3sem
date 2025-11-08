#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QDebug>
#include <QDateTime>
#include "polynom.h"

class Server : public QObject
{
    Q_OBJECT

public:
    explicit Server(QObject *parent = nullptr);
    ~Server();

    bool startServer(quint16 port);
    void stopServer();

private slots:
    void readPendingDatagrams();
    void processDatagram(const QNetworkDatagram &datagram);

private:
    Polynom p;
    QUdpSocket *m_udpSocket;
    quint16 m_port;
    bool m_isRunning;

    QByteArray processMessage(const QByteArray &data);
};

#endif // SERVER_H
