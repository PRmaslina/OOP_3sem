#ifndef APP_H
#define APP_H

#include <QMainWindow>
#include <QTimer>
#include <server.h>
#include <client.h>
#include <playerlistitem.h>
#include <serverlistitem.h>
#include <boardtile.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class App;
}
QT_END_NAMESPACE

class App : public QMainWindow
{
    Q_OBJECT

public:
    App(QWidget *parent = nullptr);
    ~App();
    Ui::App *ui;
    bool playerReady = 0;

    void clearLayout(QLayout *layout);
    void startCountdown(int startingTime, int step = 1000);
    void stopCountdown();

    void startPreparation(int n);
    void startGame(int n);
    void updateMoves(int move);
    void setEnemyMove(int x, int y, int value);
    void setMyMove(int x, int y, int value);
    int messageBox(QString text);
    void finishGame();
public slots:
    void changeSelecion();

private slots:
    void on_hostButton_clicked();

    void on_connectButton_clicked();

    void on_goBackButton_clicked();

    void on_goBackButton_2_clicked();

    void on_boardSizeSlider_valueChanged(int value);

    void on_createGameButton_clicked();

    void on_readyButton_clicked();

    void on_playerNameLEdit_editingFinished();

    void on_leaveButton_clicked();

    void on_boardSizeSlider_2_valueChanged(int value);

    void on_passwordFilter_stateChanged(int arg1);

    void on_refreshButton_clicked();

    void on_connectToServerButton_clicked();

    void updateCountdown();

    void changeTileValue();

    void on_readyButton_2_clicked();

    void makeMove();

private:
    Server* server;
    Client* client;
    Session session;
    QTimer* timer;
    int remainingTime = 10000;
    int timeStep = 1000;
    serverListItem* selectedServer = nullptr;
    QVector<BoardTile*> board;
    int boardSize;
    QVector<BoardTile*> pressedTiles;
    void blockBoard(bool);
};
#endif // APP_H
