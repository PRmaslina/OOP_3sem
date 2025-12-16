#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QByteArray>
#include <QTime>
#include <QNetworkDatagram>
#include <QVBoxLayout>

#include "message.h"
#include "session.h"
#include "player.h"
#include <boardtile.h>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    ~Client();

    bool connectToServer(QHostAddress ip, quint16 port);
    void disconnectFromServer();
    void SendToServer(MessageType type, QString message);
    void CallForServers(quint16 port, Session session);
    void updatePlayer(Player update, bool sendToServer = 0);
    void updateSession(Session update, bool sendToServer = 0);
    void setIsHost(bool);
    void setPendingSession(Session session);
    QString password;
    void setSession(Session *);
    void updateMove(int x, int y);
    void updateBoard(QVector<BoardTile *>);
private:
    QObject* parent;
    Player player;
    Session thisSession;
    QTcpSocket *tcpSocket;
    QUdpSocket *udpSocket;
    QByteArray Data;
    quint16 nextBlockSize;
    quint16 m_port;
    bool m_isHost = false;
    Session m_pendingSessionUpdate;
    QVector<Session*> Sessions;
    void processDatagram(QNetworkDatagram);
    void processMessage(MessageType, QString);
    void clearLayout(QLayout* layout);
public slots:
    void readyRead();
    void readPendingDatagrams();
};

#endif // CLIENT_H
