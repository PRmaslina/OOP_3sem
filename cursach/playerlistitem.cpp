#include "playerlistitem.h"
#include "ui_playerlistitem.h"

#include <QPainter>

PlayerListItem::PlayerListItem(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PlayerListItem) {
    ui->setupUi(this);
    player = nullptr;
}

PlayerListItem::~PlayerListItem() {
    delete ui;
    if (player) delete player;
}

void PlayerListItem::updateItem() {
    ui->name->setText(player->name);
    ui->ready->setChecked(player->ready);
}

void PlayerListItem::mark() {
    select = 1;
    update();
}

void PlayerListItem::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    if (select){
        painter.fillRect(rect(), QColor(47, 66, 107));
    }
    else {
        painter.fillRect(rect(), palette().color(QPalette::Window));
    }
    painter.setPen(QColor(200, 200, 200));
    painter.drawRect(rect().adjusted(0, 0, -1, -1));
}
