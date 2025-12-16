#include "app.h"
#include "ui_app.h"
#include <QInputDialog>
#include <QMessageBox>

App::App(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::App)
{
    ui->setupUi(this);
    server = new Server(this);
    client = new Client(this);
    ui->serverList->setAlignment(Qt::AlignTop);
    ui->playerList->setAlignment(Qt::AlignTop);
    ui->playerList_2->setAlignment(Qt::AlignTop);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &App::updateCountdown);
    ui->gameCountdownFrame->hide();
    ui->boardSizeLabel->setText(QString("%1x%1").arg(ui->boardSizeSlider->value()));
    ui->boardSizeLabel_2->setText(QString("%1x%1").arg(ui->boardSizeSlider_2->value()));
    ui->myPoints->setText("Points: 0");
    ui->enemyPoints->setText("Points: 0");
}

App::~App() {
    server->stopServer();
    delete ui;
    delete server;
    delete client;
    delete timer;
}

void App::clearLayout(QLayout* layout) {
    QLayoutItem* item;
    while ((item = layout->takeAt(0)) != nullptr) {
        if (item->widget()) {
            item->widget()->deleteLater();
        }
        delete item;
    }
}

void App::startCountdown(int startingTime, int step) {
    remainingTime = startingTime;
    ui->gameCountdownFrame->show();
    ui->remainingTimeLabel->setText(QString("%1 s").arg((float)remainingTime/1000, 0, 'f', 1));
    timeStep = step;
    timer->start(step);
}

void App::stopCountdown() {
    timer->stop();
    ui->gameCountdownFrame->hide();
    ui->remainingTimeLabel->clear();
}

void App::startPreparation(int n) {
    playerReady = 0;
    client->updatePlayer({0, ui->playerNameLEdit->text(), playerReady}, 1);
    ui->stackedWidget->setCurrentWidget(ui->myBoardPage);
    boardSize = n;
    for (int i = 0; i < n*n; i++) {
        BoardTile* tile = new BoardTile(this, i % n, i / n);
        connect(tile, &QPushButton::clicked, this, &App::changeTileValue);
        ui->board->addWidget((QWidget*)tile, tile->getY(), tile->getX());
        board.append(tile);
        ui->board->setSpacing(0);
    }
}

void App::startGame(int n) {
    ui->stackedWidget->setCurrentWidget(ui->gamePage);
    session.movesAmount = n;
    ui->movesLabel->setText(QString::number(session.movesAmount));
    for (int i = 0; i < boardSize * boardSize; i++) {
        BoardTile* tile = new BoardTile(this, i % boardSize, i / boardSize);
        BoardTile* enemyTile = new BoardTile(this, i % boardSize, i / boardSize);
        enemyTile->setEnabled(0);
        connect(tile, &QPushButton::clicked, this, &App::makeMove);
        ui->myBoard->addWidget((QWidget*)tile, tile->getY(), tile->getX());
        ui->enemyBoard->addWidget((QWidget*)enemyTile, enemyTile->getY(), enemyTile->getX());
        ui->myBoard->setSpacing(0);
        ui->enemyBoard->setSpacing(0);
    }
}

void App::updateMoves(int move) {
    blockBoard(!(move > 0));
    session.move++;
    ui->movesLabel->setText(QString::number(session.movesAmount - session.move));
    client->updatePlayer({0, ui->playerNameLEdit->text(), 0, move > 0});
    QString style = ui->myName->styleSheet();
    style = style.remove(style.indexOf("color:"), style.indexOf(';', style.indexOf("color:")) - style.indexOf("color:"));
    int myPoints = ui->myPoints->text().split(' ')[1].toInt();
    int enemyPoints = ui->enemyPoints->text().split(' ')[1].toInt();
    int finishPoints = (boardSize * (boardSize + 1)) / 2;
    if (myPoints == finishPoints || enemyPoints == finishPoints || session.movesAmount == session.move) {
        ui->myName->setStyleSheet(style + "color: #ffffff;");
        blockBoard(1);
        return;
    }
    if (move > 0) ui->myName->setStyleSheet(style + "color: #1ff250;");
    else ui->myName->setStyleSheet(style + "color: #f2261f;");
}

void App::setEnemyMove(int x, int y, int value) {
    BoardTile* tile = (BoardTile*)ui->enemyBoard->itemAtPosition(y, x)->widget();
    tile->setFixedSize(tile->geometry().size());
    tile->setValue(value);
    int points = ui->enemyPoints->text().split(' ')[1].toInt() + value;
    ui->enemyPoints->setText(QString("Points: %1").arg(points));
}

void App::setMyMove(int x, int y, int value) {
    BoardTile* tile = (BoardTile*)ui->myBoard->itemAtPosition(y, x)->widget();
    tile->setFixedSize(tile->geometry().size());
    tile->setValue(value);
    int points = ui->myPoints->text().split(' ')[1].toInt() + value;
    ui->myPoints->setText(QString("Points: %1").arg(points));
}

int App::messageBox(QString text) {
    QMessageBox msgBox(this);
    msgBox.setText(text);
    int ret = msgBox.exec();
    return ret;
}

void App::finishGame() {
    clearLayout(ui->board);
    clearLayout(ui->myBoard);
    clearLayout(ui->enemyBoard);
    ui->myPoints->setText("Points: 0");
    ui->enemyPoints->setText("Points: 0");
    ui->movesLabel->setText("");
    pressedTiles.clear();
    board.clear();
    ui->gameCountdownFrame->hide();
    playerReady = 0;
    ui->leaveButton->setEnabled(1);
    ui->readyButton->setText("Ready");
    ui->readyButton_2->setText("Ready");
    ui->readyButton_2->setEnabled(false);
    session.movesAmount = 0;
    session.move = 0;
    client->updatePlayer({0, ui->playerNameLEdit->text(), 0, 0, 0}, 1);
}

void App::changeSelecion() {
    auto clickedItem = (serverListItem*)sender();
    for (serverListItem* i : clickedItem->parent()->findChildren<serverListItem*>()) {
        i->setSelected(false);
    }
    clickedItem->setSelected(true);
    selectedServer = clickedItem;
    ui->connectToServerButton->setEnabled(true);
}

void App::on_hostButton_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->hostGamePage);
}


void App::on_connectButton_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->serverListPage);
    emit on_refreshButton_clicked();
}


void App::on_goBackButton_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->menuPage);
}


void App::on_goBackButton_2_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->menuPage);
}


void App::on_boardSizeSlider_valueChanged(int value) {
    ui->boardSizeLabel->setText(QString::number(value) + "x" + QString::number(value));
}


void App::on_createGameButton_clicked() {
    if (ui->gameNameLEdit->text().trimmed() == "") return;
    QString gameName = ui->gameNameLEdit->text();
    bool isRunning = server->startServer(8080);
    if (isRunning) {
        QHostAddress serverIp = server->getLocalIp();
        quint16 serverPort = server->getPort();
        client->connectToServer(serverIp, serverPort);
        ui->stackedWidget->setCurrentWidget(ui->waitPage);
        client->setIsHost(true);
        client->setPendingSession({serverIp, serverPort, gameName,
                                   !ui->gamePasswordLEdit->text().trimmed().isEmpty(),
                                   ui->gamePasswordLEdit->text(),
                                   ui->boardSizeSlider->value(), 0});
    }
}


void App::on_readyButton_clicked() {
    playerReady = !playerReady;
    client->updatePlayer({0, ui->playerNameLEdit->text(), playerReady}, 1);
    ui->leaveButton->setEnabled(!playerReady);
    if (playerReady) ui->readyButton->setText("Not Ready");
    else ui->readyButton->setText("Ready");
}


void App::on_playerNameLEdit_editingFinished() {
    client->updatePlayer({0, ui->playerNameLEdit->text(), playerReady});
}


void App::on_leaveButton_clicked() {
    client->disconnectFromServer();
    playerReady = false;
    ui->readyButton->setText("Ready");
    ui->stackedWidget->setCurrentWidget(ui->menuPage);
}


void App::on_boardSizeSlider_2_valueChanged(int value) {
    session.boardSize = value;
    ui->boardSizeLabel_2->setText(QString::number(value) + "x" + QString::number(value));
}


void App::on_passwordFilter_stateChanged(int arg1) {
    session.hasPassword = arg1;
}


void App::on_refreshButton_clicked() {
    ui->connectToServerButton->setEnabled(false);
    clearLayout(ui->serverList);
    selectedServer = nullptr;
    session.boardSize = ui->boardSizeSlider_2->value();
    session.hasPassword = ui->passwordFilter->checkState();
    client->CallForServers(8080, session);
}


void App::on_connectToServerButton_clicked() {
    if (selectedServer->session->hasPassword) {
        bool ok;
        client->password = QInputDialog::getText(this,
                                             "Password",
                                             "Input password:",
                                             QLineEdit::Normal,
                                             "", // значение по умолчанию
                                             &ok);
        if (ok && !client->password.isEmpty()) {
            qDebug() << "[App] password:" << client->password;
        }

    }
    bool connected = client->connectToServer(selectedServer->session->serverAddress, selectedServer->session->serverPort);
    if (connected) client->setSession(selectedServer->session);
}

void App::updateCountdown() {
    remainingTime -= timeStep;
    if (remainingTime <= 0) {
        timer->stop();
        ui->remainingTimeLabel->setText("0.0 s");
    }
    else ui->remainingTimeLabel->setText(QString("%1 s").arg((float)remainingTime/1000, 0, 'f', 1));
}

void App::changeTileValue() {
    auto* tile = (BoardTile*)sender();
    tile->setFixedSize(tile->geometry().size());
    qDebug() << "[App] tile:" << tile->getX() << tile->getY();
    if (!(pressedTiles.size() < boardSize || tile->getValue() > 0)) return;
    ui->readyButton_2->setEnabled(0);
    if (!tile->isPressed()) {
        pressedTiles.append(tile);
        tile->setValue(pressedTiles.size());
        if (pressedTiles.size() == boardSize) ui->readyButton_2->setEnabled(1);
        qDebug() << "[App] tile pressed(1) :" << tile->getValue() << ":" << pressedTiles;
        if (!(tile->getX() % boardSize == 0)) board[tile->getY()*boardSize + tile->getX() - 1]->block(0);
        if (!(tile->getX() % boardSize == boardSize - 1)) board[tile->getY()*boardSize + tile->getX() + 1]->block(0);
        if (!(tile->getY() % boardSize == 0)) board[(tile->getY() - 1)*boardSize + tile->getX()]->block(0);
        if (!(tile->getY() % boardSize == boardSize - 1)) board[(tile->getY() + 1)*boardSize + tile->getX()]->block(0);
    }
    else {
        int rmi = 0;
        for (int i = 0; i < pressedTiles.size(); i++) {
            pressedTiles[i]->setValue(1 + i + ((tile->getValue() < i + 1)?-1:0));
            if (pressedTiles[i] == tile) rmi = i;
        }
        pressedTiles.remove(rmi);
        tile->unpress();
        qDebug() << "[App] pressed(0) :" << tile->getValue() << ":" << pressedTiles;
        if (!(tile->getX() % boardSize == 0)) board[tile->getY()*boardSize + tile->getX() - 1]->block(1);
        if (!(tile->getX() % boardSize == boardSize - 1)) board[tile->getY()*boardSize + tile->getX() + 1]->block(1);
        if (!(tile->getY() % boardSize == 0)) board[(tile->getY() - 1)*boardSize + tile->getX()]->block(1);
        if (!(tile->getY() % boardSize == boardSize - 1)) board[(tile->getY() + 1)*boardSize + tile->getX()]->block(1);
    }
}


void App::on_readyButton_2_clicked() {
    playerReady = !playerReady;
    if (playerReady) ui->readyButton_2->setText("Not Ready");
    else ui->readyButton_2->setText("Ready");
    for (auto tile : board) {
        tile->block(!playerReady, 0);
    }
    if (playerReady) client->updateBoard(pressedTiles);
    client->updatePlayer({0, ui->playerNameLEdit->text(), playerReady}, 1);
}

void App::makeMove() {
    BoardTile* tile = (BoardTile*)sender();
    tile->block(0, 0);
    client->updateMove(tile->getX(), tile->getY());
}

void App::blockBoard(bool block) {
    for (int i = 0; i < boardSize * boardSize; i++) {
        BoardTile* tile = (BoardTile*)ui->myBoard->itemAtPosition(i / boardSize, i % boardSize)->widget();
        tile->block(!block, 0);
    }
}

