#ifndef BoardTile_H
#define BoardTile_H

#include <QWidget>
#include <QPushButton>
#include <QString>

class BoardTile : public QPushButton {
    Q_OBJECT

private:
    int x;
    int y;
    int value = 0;
    bool pressed = 0;
    int blockDeep = 0;
protected: /*
    void showEvent(QShowEvent* event) override {
        QWidget::showEvent(event);
        qDebug() << this->sizeHint();
        qDebug() << this->geometry();
        qDebug() << "---";
    } */
public:
    explicit BoardTile(QWidget *parent = nullptr, int coordX = 0, int coordY = 0);
    int getX();
    int getY();
    void setPos(int coordX, int coordY);
    void setValue(int v);
    int getValue();
    bool isPressed();
    void unpress();
    void block(bool v, bool changeColor = 1);
};

#endif
