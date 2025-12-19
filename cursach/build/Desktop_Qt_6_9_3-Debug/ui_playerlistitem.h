/********************************************************************************
** Form generated from reading UI file 'playerlistitem.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYERLISTITEM_H
#define UI_PLAYERLISTITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlayerListItem
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *name;
    QCheckBox *ready;

    void setupUi(QWidget *PlayerListItem)
    {
        if (PlayerListItem->objectName().isEmpty())
            PlayerListItem->setObjectName("PlayerListItem");
        PlayerListItem->setWindowModality(Qt::WindowModality::NonModal);
        PlayerListItem->resize(242, 40);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PlayerListItem->sizePolicy().hasHeightForWidth());
        PlayerListItem->setSizePolicy(sizePolicy);
        PlayerListItem->setMinimumSize(QSize(0, 40));
        PlayerListItem->setMaximumSize(QSize(16777215, 40));
        PlayerListItem->setContextMenuPolicy(Qt::ContextMenuPolicy::NoContextMenu);
        horizontalLayoutWidget = new QWidget(PlayerListItem);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(10, 10, 221, 21));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        name = new QLabel(horizontalLayoutWidget);
        name->setObjectName("name");
        sizePolicy.setHeightForWidth(name->sizePolicy().hasHeightForWidth());
        name->setSizePolicy(sizePolicy);
        name->setStyleSheet(QString::fromUtf8("font: oblique 14pt \"URW Gothic\";"));

        horizontalLayout->addWidget(name);

        ready = new QCheckBox(horizontalLayoutWidget);
        ready->setObjectName("ready");
        ready->setEnabled(false);
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(ready->sizePolicy().hasHeightForWidth());
        ready->setSizePolicy(sizePolicy1);
        ready->setMouseTracking(false);
        ready->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        ready->setContextMenuPolicy(Qt::ContextMenuPolicy::NoContextMenu);
        ready->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        ready->setCheckable(true);
        ready->setChecked(false);
        ready->setTristate(false);

        horizontalLayout->addWidget(ready);


        retranslateUi(PlayerListItem);

        QMetaObject::connectSlotsByName(PlayerListItem);
    } // setupUi

    void retranslateUi(QWidget *PlayerListItem)
    {
        PlayerListItem->setWindowTitle(QCoreApplication::translate("PlayerListItem", "Form", nullptr));
        name->setText(QString());
        ready->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class PlayerListItem: public Ui_PlayerListItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYERLISTITEM_H
