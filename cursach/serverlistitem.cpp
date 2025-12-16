#include "serverlistitem.h"
#include "ui_serverlistitem.h"

serverListItem::serverListItem(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::serverListItem) {

    ui->setupUi(this);
}

serverListItem::~serverListItem()
{
    delete ui;
    if (session) delete session;
}

void serverListItem::updateThis() {
    ui->gameName->setText(session->name);
    ui->isProtected->setChecked(session->hasPassword);
    ui->boardSize->setText(QString("%1x%1").arg(session->boardSize));
    ui->playersAmount->setText(QString::number(session->playersAmount)+"/2");
}

void serverListItem::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        m_pressed = true;
        update();
    }
    QWidget::mousePressEvent(event);
}

void serverListItem::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && m_pressed) {
        m_pressed = false;

        if (rect().contains(event->pos())) {
            emit clicked();
        }
        update();
    } else if (event->button() == Qt::RightButton) {
        emit rightClicked();
    }
    QWidget::mouseReleaseEvent(event);
}

void serverListItem::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);

    QColor bgColor;
    if (m_selected) {
        bgColor = QColor(47, 66, 107);
    } else {
        bgColor = palette().color(QPalette::Window);
    }

    painter.fillRect(rect(), bgColor);

    // Рамка
    painter.setPen(m_selected ? QColor(0, 100, 200) : QColor(200, 200, 200));
    painter.drawRect(rect().adjusted(0, 0, -1, -1));
}

void serverListItem::setSelected(bool selected) {
    if (this->m_selected != selected) {
        this->m_selected = selected;
        update();
    }
}
