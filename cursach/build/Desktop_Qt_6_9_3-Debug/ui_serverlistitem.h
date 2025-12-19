/********************************************************************************
** Form generated from reading UI file 'serverlistitem.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVERLISTITEM_H
#define UI_SERVERLISTITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_serverListItem
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *gameName;
    QCheckBox *isProtected;
    QLabel *boardSize;
    QLabel *playersAmount;

    void setupUi(QWidget *serverListItem)
    {
        if (serverListItem->objectName().isEmpty())
            serverListItem->setObjectName("serverListItem");
        serverListItem->resize(444, 40);
        serverListItem->setMinimumSize(QSize(0, 40));
        serverListItem->setMaximumSize(QSize(16777215, 40));
        layoutWidget = new QWidget(serverListItem);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 10, 423, 22));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        gameName = new QLabel(layoutWidget);
        gameName->setObjectName("gameName");
        gameName->setMinimumSize(QSize(200, 0));

        horizontalLayout->addWidget(gameName);

        isProtected = new QCheckBox(layoutWidget);
        isProtected->setObjectName("isProtected");
        isProtected->setEnabled(false);
        isProtected->setCheckable(true);
        isProtected->setTristate(true);

        horizontalLayout->addWidget(isProtected);

        boardSize = new QLabel(layoutWidget);
        boardSize->setObjectName("boardSize");
        boardSize->setMinimumSize(QSize(50, 0));
        boardSize->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout->addWidget(boardSize);

        playersAmount = new QLabel(layoutWidget);
        playersAmount->setObjectName("playersAmount");
        playersAmount->setMinimumSize(QSize(50, 0));
        playersAmount->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout->addWidget(playersAmount);


        retranslateUi(serverListItem);

        QMetaObject::connectSlotsByName(serverListItem);
    } // setupUi

    void retranslateUi(QWidget *serverListItem)
    {
        serverListItem->setWindowTitle(QCoreApplication::translate("serverListItem", "Form", nullptr));
        gameName->setText(QString());
        isProtected->setText(QCoreApplication::translate("serverListItem", "protected", nullptr));
        boardSize->setText(QCoreApplication::translate("serverListItem", "3x3", nullptr));
        playersAmount->setText(QCoreApplication::translate("serverListItem", "0/2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class serverListItem: public Ui_serverListItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVERLISTITEM_H
