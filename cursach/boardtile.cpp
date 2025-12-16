#include "boardtile.h"

BoardTile::BoardTile(QWidget *parent, int coordX, int coordY) : QPushButton(parent) {
    this->setText("");
    this->resize(100, 100);
    QSizePolicy policy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    this->setSizePolicy(policy);
    x = coordX;
    y = coordY;
    this->setPalette(QPalette(QColor(136, 140, 155)));
}

int BoardTile::getX() {
    return x;
}

int BoardTile::getY() {
    return y;
}

void BoardTile::setPos(int coordX, int coordY)
{
    x = coordX;
    y = coordY;
}

void BoardTile::setValue(int v) {
    value = v;
    pressed = 1;
    this->setText(QString::number(value));
    this->setPalette(QPalette(QColor(116, 133, 193)));
}

int BoardTile::getValue() {
    return value;
}

bool BoardTile::isPressed() {
    return pressed;
}

void BoardTile::unpress() {
    value = 0;
    pressed = 0;
    this->setText("");
    this->setPalette(QPalette(QColor(136, 140, 155)));
}

void BoardTile::block(bool v, bool changeColor) {
    if (v && blockDeep == 0) return;
    blockDeep += 1 + v*(-2);
    this->setEnabled(blockDeep == 0);
    if (!changeColor) return;
    if (!(blockDeep == 0)) this->setPalette(QPalette(QColor(47, 66, 107)));
    else this->setPalette(QPalette(QColor(136, 140, 155)));
}
