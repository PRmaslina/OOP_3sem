/********************************************************************************
** Form generated from reading UI file 'app.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APP_H
#define UI_APP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_App
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QStackedWidget *stackedWidget;
    QWidget *menuPage;
    QPushButton *hostButton;
    QPushButton *connectButton;
    QLineEdit *playerNameLEdit;
    QWidget *hostGamePage;
    QPushButton *goBackButton;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_3;
    QFrame *frame_2;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout_4;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *gameNameLEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *gamePasswordLEdit;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QLabel *label_3;
    QSlider *boardSizeSlider;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QLabel *boardSizeLabel;
    QPushButton *createGameButton;
    QWidget *serverListPage;
    QWidget *layoutWidget2;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_4;
    QFrame *frame;
    QWidget *layoutWidget3;
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer_5;
    QLabel *boardSizeLabel_2;
    QRadioButton *onlineFilter;
    QRadioButton *localFilter;
    QCheckBox *passwordFilter;
    QLabel *label_4;
    QPushButton *refreshButton;
    QSlider *boardSizeSlider_2;
    QPushButton *connectToServerButton;
    QPushButton *goBackButton_2;
    QVBoxLayout *serverList;
    QWidget *waitPage;
    QFrame *frame_3;
    QLabel *label_5;
    QFrame *frame_4;
    QWidget *layoutWidget_2;
    QVBoxLayout *playerList;
    QPushButton *leaveButton;
    QPushButton *readyButton;
    QLabel *gameNameLabel;
    QFrame *gameCountdownFrame;
    QLabel *label_6;
    QLabel *remainingTimeLabel;
    QWidget *myBoardPage;
    QWidget *gridLayoutWidget_3;
    QGridLayout *board;
    QPushButton *readyButton_2;
    QFrame *frame_5;
    QLabel *label_7;
    QFrame *frame_6;
    QWidget *layoutWidget_3;
    QVBoxLayout *playerList_2;
    QWidget *gamePage;
    QWidget *gridLayoutWidget;
    QGridLayout *myBoard;
    QWidget *gridLayoutWidget_2;
    QGridLayout *enemyBoard;
    QLabel *myName;
    QLabel *enemyName;
    QLabel *myPoints;
    QLabel *enemyPoints;
    QLabel *movesLabel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *App)
    {
        if (App->objectName().isEmpty())
            App->setObjectName("App");
        App->resize(800, 600);
        centralwidget = new QWidget(App);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        menuPage = new QWidget();
        menuPage->setObjectName("menuPage");
        hostButton = new QPushButton(menuPage);
        hostButton->setObjectName("hostButton");
        hostButton->setGeometry(QRect(300, 180, 151, 31));
        connectButton = new QPushButton(menuPage);
        connectButton->setObjectName("connectButton");
        connectButton->setGeometry(QRect(300, 250, 151, 31));
        playerNameLEdit = new QLineEdit(menuPage);
        playerNameLEdit->setObjectName("playerNameLEdit");
        playerNameLEdit->setGeometry(QRect(620, 190, 113, 22));
        stackedWidget->addWidget(menuPage);
        hostGamePage = new QWidget();
        hostGamePage->setObjectName("hostGamePage");
        goBackButton = new QPushButton(hostGamePage);
        goBackButton->setObjectName("goBackButton");
        goBackButton->setGeometry(QRect(42, 507, 80, 23));
        layoutWidget = new QWidget(hostGamePage);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(30, 20, 231, 281));
        verticalLayout_3 = new QVBoxLayout(layoutWidget);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        frame_2 = new QFrame(layoutWidget);
        frame_2->setObjectName("frame_2");
        frame_2->setFrameShape(QFrame::Shape::StyledPanel);
        frame_2->setFrameShadow(QFrame::Shadow::Raised);
        layoutWidget1 = new QWidget(frame_2);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(10, 10, 205, 127));
        gridLayout_4 = new QGridLayout(layoutWidget1);
        gridLayout_4->setObjectName("gridLayout_4");
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(layoutWidget1);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        gameNameLEdit = new QLineEdit(layoutWidget1);
        gameNameLEdit->setObjectName("gameNameLEdit");

        horizontalLayout->addWidget(gameNameLEdit);


        gridLayout_4->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        gamePasswordLEdit = new QLineEdit(layoutWidget1);
        gamePasswordLEdit->setObjectName("gamePasswordLEdit");

        horizontalLayout_2->addWidget(gamePasswordLEdit);


        gridLayout_4->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label_3 = new QLabel(layoutWidget1);
        label_3->setObjectName("label_3");

        verticalLayout->addWidget(label_3);

        boardSizeSlider = new QSlider(layoutWidget1);
        boardSizeSlider->setObjectName("boardSizeSlider");
        boardSizeSlider->setMinimum(4);
        boardSizeSlider->setMaximum(12);
        boardSizeSlider->setPageStep(1);
        boardSizeSlider->setOrientation(Qt::Orientation::Horizontal);
        boardSizeSlider->setTickPosition(QSlider::TickPosition::TicksBothSides);
        boardSizeSlider->setTickInterval(1);

        verticalLayout->addWidget(boardSizeSlider);


        horizontalLayout_3->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        boardSizeLabel = new QLabel(layoutWidget1);
        boardSizeLabel->setObjectName("boardSizeLabel");
        boardSizeLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(boardSizeLabel);


        horizontalLayout_3->addLayout(verticalLayout_2);


        gridLayout_4->addLayout(horizontalLayout_3, 2, 0, 1, 1);


        verticalLayout_3->addWidget(frame_2);

        createGameButton = new QPushButton(layoutWidget);
        createGameButton->setObjectName("createGameButton");

        verticalLayout_3->addWidget(createGameButton);

        stackedWidget->addWidget(hostGamePage);
        serverListPage = new QWidget();
        serverListPage->setObjectName("serverListPage");
        layoutWidget2 = new QWidget(serverListPage);
        layoutWidget2->setObjectName("layoutWidget2");
        layoutWidget2->setGeometry(QRect(4, 0, 771, 531));
        gridLayout_3 = new QGridLayout(layoutWidget2);
        gridLayout_3->setObjectName("gridLayout_3");
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);
        frame = new QFrame(layoutWidget2);
        frame->setObjectName("frame");
        frame->setMinimumSize(QSize(180, 0));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        layoutWidget3 = new QWidget(frame);
        layoutWidget3->setObjectName("layoutWidget3");
        layoutWidget3->setGeometry(QRect(10, 10, 161, 431));
        gridLayout_2 = new QGridLayout(layoutWidget3);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_2->addItem(verticalSpacer_5, 5, 0, 1, 1);

        boardSizeLabel_2 = new QLabel(layoutWidget3);
        boardSizeLabel_2->setObjectName("boardSizeLabel_2");

        gridLayout_2->addWidget(boardSizeLabel_2, 3, 1, 1, 1);

        onlineFilter = new QRadioButton(layoutWidget3);
        onlineFilter->setObjectName("onlineFilter");

        gridLayout_2->addWidget(onlineFilter, 1, 0, 1, 2);

        localFilter = new QRadioButton(layoutWidget3);
        localFilter->setObjectName("localFilter");
        localFilter->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        localFilter->setChecked(true);

        gridLayout_2->addWidget(localFilter, 0, 0, 1, 2);

        passwordFilter = new QCheckBox(layoutWidget3);
        passwordFilter->setObjectName("passwordFilter");
        passwordFilter->setChecked(true);

        gridLayout_2->addWidget(passwordFilter, 2, 0, 1, 2);

        label_4 = new QLabel(layoutWidget3);
        label_4->setObjectName("label_4");

        gridLayout_2->addWidget(label_4, 3, 0, 1, 1);

        refreshButton = new QPushButton(layoutWidget3);
        refreshButton->setObjectName("refreshButton");

        gridLayout_2->addWidget(refreshButton, 6, 0, 1, 2);

        boardSizeSlider_2 = new QSlider(layoutWidget3);
        boardSizeSlider_2->setObjectName("boardSizeSlider_2");
        boardSizeSlider_2->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        boardSizeSlider_2->setMinimum(4);
        boardSizeSlider_2->setMaximum(12);
        boardSizeSlider_2->setPageStep(1);
        boardSizeSlider_2->setValue(12);
        boardSizeSlider_2->setOrientation(Qt::Orientation::Horizontal);
        boardSizeSlider_2->setInvertedAppearance(false);
        boardSizeSlider_2->setInvertedControls(false);
        boardSizeSlider_2->setTickPosition(QSlider::TickPosition::TicksBothSides);
        boardSizeSlider_2->setTickInterval(1);

        gridLayout_2->addWidget(boardSizeSlider_2, 4, 0, 1, 2);


        verticalLayout_4->addWidget(frame);

        connectToServerButton = new QPushButton(layoutWidget2);
        connectToServerButton->setObjectName("connectToServerButton");
        connectToServerButton->setEnabled(false);

        verticalLayout_4->addWidget(connectToServerButton);


        gridLayout_3->addLayout(verticalLayout_4, 0, 2, 2, 1);

        goBackButton_2 = new QPushButton(layoutWidget2);
        goBackButton_2->setObjectName("goBackButton_2");

        gridLayout_3->addWidget(goBackButton_2, 1, 0, 1, 1);

        serverList = new QVBoxLayout();
        serverList->setObjectName("serverList");

        gridLayout_3->addLayout(serverList, 0, 0, 1, 2);

        stackedWidget->addWidget(serverListPage);
        waitPage = new QWidget();
        waitPage->setObjectName("waitPage");
        frame_3 = new QFrame(waitPage);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(190, 80, 371, 311));
        frame_3->setFrameShape(QFrame::Shape::StyledPanel);
        frame_3->setFrameShadow(QFrame::Shadow::Raised);
        label_5 = new QLabel(frame_3);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(70, 10, 221, 61));
        label_5->setStyleSheet(QString::fromUtf8("font: italic 24pt \"Verdana\";"));
        label_5->setAlignment(Qt::AlignmentFlag::AlignCenter);
        frame_4 = new QFrame(frame_3);
        frame_4->setObjectName("frame_4");
        frame_4->setGeometry(QRect(20, 80, 331, 211));
        frame_4->setFrameShape(QFrame::Shape::StyledPanel);
        frame_4->setFrameShadow(QFrame::Shadow::Raised);
        layoutWidget_2 = new QWidget(frame_4);
        layoutWidget_2->setObjectName("layoutWidget_2");
        layoutWidget_2->setGeometry(QRect(11, 9, 311, 191));
        playerList = new QVBoxLayout(layoutWidget_2);
        playerList->setObjectName("playerList");
        playerList->setContentsMargins(0, 0, 0, 0);
        leaveButton = new QPushButton(waitPage);
        leaveButton->setObjectName("leaveButton");
        leaveButton->setGeometry(QRect(20, 500, 84, 23));
        readyButton = new QPushButton(waitPage);
        readyButton->setObjectName("readyButton");
        readyButton->setGeometry(QRect(680, 500, 84, 23));
        gameNameLabel = new QLabel(waitPage);
        gameNameLabel->setObjectName("gameNameLabel");
        gameNameLabel->setGeometry(QRect(190, 10, 371, 61));
        gameNameLabel->setStyleSheet(QString::fromUtf8("font: 700 30pt \"Verdana\";"));
        gameNameLabel->setFrameShape(QFrame::Shape::NoFrame);
        gameNameLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        gameCountdownFrame = new QFrame(waitPage);
        gameCountdownFrame->setObjectName("gameCountdownFrame");
        gameCountdownFrame->setEnabled(true);
        gameCountdownFrame->setGeometry(QRect(580, 120, 181, 161));
        gameCountdownFrame->setFrameShape(QFrame::Shape::StyledPanel);
        gameCountdownFrame->setFrameShadow(QFrame::Shadow::Raised);
        label_6 = new QLabel(gameCountdownFrame);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 10, 161, 61));
        label_6->setStyleSheet(QString::fromUtf8("font: italic 16pt \"Verdana\";"));
        label_6->setAlignment(Qt::AlignmentFlag::AlignCenter);
        remainingTimeLabel = new QLabel(gameCountdownFrame);
        remainingTimeLabel->setObjectName("remainingTimeLabel");
        remainingTimeLabel->setGeometry(QRect(10, 90, 161, 61));
        remainingTimeLabel->setStyleSheet(QString::fromUtf8("font: italic 16pt \"Verdana\";"));
        remainingTimeLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        stackedWidget->addWidget(waitPage);
        myBoardPage = new QWidget();
        myBoardPage->setObjectName("myBoardPage");
        gridLayoutWidget_3 = new QWidget(myBoardPage);
        gridLayoutWidget_3->setObjectName("gridLayoutWidget_3");
        gridLayoutWidget_3->setGeometry(QRect(50, 60, 331, 331));
        board = new QGridLayout(gridLayoutWidget_3);
        board->setObjectName("board");
        board->setContentsMargins(0, 0, 0, 0);
        readyButton_2 = new QPushButton(myBoardPage);
        readyButton_2->setObjectName("readyButton_2");
        readyButton_2->setEnabled(false);
        readyButton_2->setGeometry(QRect(50, 450, 331, 51));
        frame_5 = new QFrame(myBoardPage);
        frame_5->setObjectName("frame_5");
        frame_5->setGeometry(QRect(440, 80, 331, 261));
        frame_5->setFrameShape(QFrame::Shape::StyledPanel);
        frame_5->setFrameShadow(QFrame::Shadow::Raised);
        label_7 = new QLabel(frame_5);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(20, 10, 221, 31));
        label_7->setStyleSheet(QString::fromUtf8("font: italic 18pt \"Verdana\";"));
        label_7->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        frame_6 = new QFrame(frame_5);
        frame_6->setObjectName("frame_6");
        frame_6->setGeometry(QRect(0, 50, 331, 211));
        frame_6->setFrameShape(QFrame::Shape::StyledPanel);
        frame_6->setFrameShadow(QFrame::Shadow::Raised);
        layoutWidget_3 = new QWidget(frame_6);
        layoutWidget_3->setObjectName("layoutWidget_3");
        layoutWidget_3->setGeometry(QRect(12, 10, 311, 191));
        playerList_2 = new QVBoxLayout(layoutWidget_3);
        playerList_2->setObjectName("playerList_2");
        playerList_2->setContentsMargins(0, 0, 0, 0);
        stackedWidget->addWidget(myBoardPage);
        gamePage = new QWidget();
        gamePage->setObjectName("gamePage");
        gridLayoutWidget = new QWidget(gamePage);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(20, 100, 331, 331));
        myBoard = new QGridLayout(gridLayoutWidget);
        myBoard->setObjectName("myBoard");
        myBoard->setContentsMargins(0, 0, 0, 0);
        gridLayoutWidget_2 = new QWidget(gamePage);
        gridLayoutWidget_2->setObjectName("gridLayoutWidget_2");
        gridLayoutWidget_2->setGeometry(QRect(430, 100, 331, 331));
        enemyBoard = new QGridLayout(gridLayoutWidget_2);
        enemyBoard->setObjectName("enemyBoard");
        enemyBoard->setContentsMargins(0, 0, 0, 0);
        myName = new QLabel(gamePage);
        myName->setObjectName("myName");
        myName->setGeometry(QRect(20, 20, 331, 61));
        myName->setStyleSheet(QString::fromUtf8("font: 700 30pt \"Verdana\"; color: #ffffff;"));
        myName->setFrameShape(QFrame::Shape::StyledPanel);
        myName->setFrameShadow(QFrame::Shadow::Plain);
        myName->setAlignment(Qt::AlignmentFlag::AlignCenter);
        enemyName = new QLabel(gamePage);
        enemyName->setObjectName("enemyName");
        enemyName->setGeometry(QRect(430, 20, 331, 61));
        enemyName->setStyleSheet(QString::fromUtf8("font: 700 30pt \"Verdana\";"));
        enemyName->setFrameShape(QFrame::Shape::StyledPanel);
        enemyName->setAlignment(Qt::AlignmentFlag::AlignCenter);
        myPoints = new QLabel(gamePage);
        myPoints->setObjectName("myPoints");
        myPoints->setGeometry(QRect(20, 440, 331, 61));
        myPoints->setStyleSheet(QString::fromUtf8("font: 700 30pt \"Verdana\";"));
        myPoints->setFrameShape(QFrame::Shape::StyledPanel);
        myPoints->setFrameShadow(QFrame::Shadow::Plain);
        myPoints->setAlignment(Qt::AlignmentFlag::AlignCenter);
        enemyPoints = new QLabel(gamePage);
        enemyPoints->setObjectName("enemyPoints");
        enemyPoints->setGeometry(QRect(430, 440, 331, 61));
        enemyPoints->setStyleSheet(QString::fromUtf8("font: 700 30pt \"Verdana\";"));
        enemyPoints->setFrameShape(QFrame::Shape::StyledPanel);
        enemyPoints->setFrameShadow(QFrame::Shadow::Plain);
        enemyPoints->setAlignment(Qt::AlignmentFlag::AlignCenter);
        movesLabel = new QLabel(gamePage);
        movesLabel->setObjectName("movesLabel");
        movesLabel->setGeometry(QRect(360, 20, 61, 61));
        movesLabel->setStyleSheet(QString::fromUtf8("font: 700 30pt \"Verdana\";"));
        movesLabel->setFrameShape(QFrame::Shape::StyledPanel);
        movesLabel->setFrameShadow(QFrame::Shadow::Plain);
        movesLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        stackedWidget->addWidget(gamePage);

        gridLayout->addWidget(stackedWidget, 0, 0, 1, 1);

        App->setCentralWidget(centralwidget);
        menubar = new QMenuBar(App);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 20));
        App->setMenuBar(menubar);
        statusbar = new QStatusBar(App);
        statusbar->setObjectName("statusbar");
        App->setStatusBar(statusbar);

        retranslateUi(App);

        QMetaObject::connectSlotsByName(App);
    } // setupUi

    void retranslateUi(QMainWindow *App)
    {
        App->setWindowTitle(QCoreApplication::translate("App", "App", nullptr));
        hostButton->setText(QCoreApplication::translate("App", "Host game", nullptr));
        connectButton->setText(QCoreApplication::translate("App", "Server list", nullptr));
        playerNameLEdit->setText(QCoreApplication::translate("App", "Player0", nullptr));
        goBackButton->setText(QCoreApplication::translate("App", "Back", nullptr));
        label->setText(QCoreApplication::translate("App", "Game name", nullptr));
        label_2->setText(QCoreApplication::translate("App", "Password", nullptr));
        label_3->setText(QCoreApplication::translate("App", "Board size", nullptr));
        boardSizeLabel->setText(QCoreApplication::translate("App", "3x3", nullptr));
        createGameButton->setText(QCoreApplication::translate("App", "Create game", nullptr));
        boardSizeLabel_2->setText(QString());
        onlineFilter->setText(QCoreApplication::translate("App", "Online", nullptr));
        localFilter->setText(QCoreApplication::translate("App", "Local", nullptr));
        passwordFilter->setText(QCoreApplication::translate("App", "Can have password?", nullptr));
        label_4->setText(QCoreApplication::translate("App", "Board Size", nullptr));
        refreshButton->setText(QCoreApplication::translate("App", "Refresh", nullptr));
        connectToServerButton->setText(QCoreApplication::translate("App", "Connect", nullptr));
        goBackButton_2->setText(QCoreApplication::translate("App", "Back", nullptr));
        label_5->setText(QCoreApplication::translate("App", "Players", nullptr));
        leaveButton->setText(QCoreApplication::translate("App", "Leave", nullptr));
        readyButton->setText(QCoreApplication::translate("App", "Ready", nullptr));
        gameNameLabel->setText(QString());
        label_6->setText(QCoreApplication::translate("App", "The Game\n"
" will start in", nullptr));
        remainingTimeLabel->setText(QString());
        readyButton_2->setText(QCoreApplication::translate("App", "Ready", nullptr));
        label_7->setText(QCoreApplication::translate("App", "Players", nullptr));
        myName->setText(QString());
        enemyName->setText(QString());
        myPoints->setText(QString());
        enemyPoints->setText(QString());
        movesLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class App: public Ui_App {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APP_H
