#ifndef SERVERLISTITEM_H
#define SERVERLISTITEM_H

#include <session.h>
#include <QObject>
#include <QWidget>
#include <QString>
#include <QMouseEvent>
#include <QPainter>

namespace Ui {
class serverListItem;
}

class serverListItem : public QWidget
{
    Q_OBJECT

public:
    explicit serverListItem(QWidget *parent = nullptr);
    ~serverListItem();
    void updateThis();
    void setSelected(bool);
    Session* session = nullptr;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

signals:  // <-- Объявление сигналов
    void clicked();
    void rightClicked();
    void doubleClicked();

private:
    Ui::serverListItem *ui;
    bool m_selected = false;
    bool m_pressed = false;

};

#endif // SERVERLISTITEM_H
