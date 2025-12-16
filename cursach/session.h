#ifndef SESSION_H
#define SESSION_H

#include <QString>
#include <QHostAddress>

struct Session {
    QHostAddress serverAddress;
    quint16 serverPort;
    QString name;
    bool hasPassword;
    QString password;
    int boardSize;
    int playersAmount;
    int maxPlayers = 2;
    int gameState = 0;
    int move = 0;
    int movesAmount = 0;
};

#endif // SESSION_H
