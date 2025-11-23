#ifndef APP_H
#define APP_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QNetworkDatagram>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void start();
private slots:
    void on_OutputType1Button_clicked();
    void on_OutputType2Button_clicked();
    void on_PolynomInputButton_clicked();
    void on_PointButton_clicked();
    void on_RealNumbersButton_clicked();
    void on_ComplexNumbersButton_clicked();

    void readPendingDatagrams();
private:
    Ui::MainWindow *ui;
    QString session = "{}";
    QUdpSocket *udpSocket;
    QString serverAddress;
    quint16 serverPort;
    bool useComplexNumbers = false; // Флаг для выбора типа чисел

    int tryConnect(QString _serverAddress, quint16 _serverPort);
    void sendToServer(QByteArray datagram);
    void setNumberType(bool useComplex); // Новый метод
};
#endif // APP_H
