#ifndef PLAYERLISTITEM_H
#define PLAYERLISTITEM_H

#include <QWidget>
#include <QTcpSocket>
#include "player.h"

namespace Ui {
class PlayerListItem;
}

class PlayerListItem : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerListItem(QWidget *parent = nullptr);
    ~PlayerListItem();

    void updateItem();
    void mark();
    Player* player;
protected:
    void paintEvent(QPaintEvent* event) override;
private:
    Ui::PlayerListItem *ui;
    bool select = 0;
};

#endif // PLAYERLISTITEM_H
