#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include <QVector>
#include <tile.h>

struct Player {
    int id = 0;
    QString name = "";
    bool ready = 0;
    bool move = 0;
    int points = 0;
    QVector<Tile> tiles;
};

#endif // PLAYER_H
