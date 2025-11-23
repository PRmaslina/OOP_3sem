#include "app.h"
#include "ui_app.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    udpSocket = new QUdpSocket(this);
    ui = new Ui::MainWindow;
    this->tryConnect("127.0.0.1", 2040);
    ui->setupUi(this);
}

int MainWindow::tryConnect(QString _serverAddress, quint16 _serverPort){
    connect(udpSocket, &QUdpSocket::readyRead, this, &MainWindow::readPendingDatagrams);
    udpSocket->bind(QHostAddress(_serverAddress), _serverPort);

    serverAddress = _serverAddress;
    serverPort = _serverPort;
    sendToServer("{}0");
    return 1;
}

MainWindow::~MainWindow()
{
    QString response = session + "1";
    sendToServer(response.toUtf8());
    delete ui;
}

void MainWindow::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = udpSocket->receiveDatagram();
        if (!datagram.isValid()) {
            qDebug() << "Error reading datagram";
            continue;
        }

        QByteArray data = datagram.data();
        QString message = QString::fromUtf8(data);
        int command = message[0].digitValue();
        message[0] = ' ';
        switch(command) {
        case 0: {
                ui->Log->setText("Подключён к серверу");
                session = message;
                break;
            }
        case 1: {
                ui->Log->setText("Сервер отключён");
            }
        case 2: {
                ui->Log->setText("Тип вывода изменён на: вывод с коэффициентами");
                ui->PolynomOut->setText(message);
                break;
            }
        case 3: {
                ui->Log->setText("Тип вывода изменён на: вывод с корнями");
                ui->PolynomOut->setText(message);
                break;
            }
        case 4: {
                ui->PolynomOut->setText(message);
                break;
            }
        case 5: {
                ui->OutputSolve->setText(message);
                break;
            }
        case 6: {
                ui->Log->setText(message);
                break;
            }
        }
    }
}

void MainWindow::sendToServer(QByteArray datagram) {
    udpSocket->writeDatagram(datagram, QHostAddress(serverAddress), serverPort);
}

void MainWindow::on_OutputType1Button_clicked()
{

    QString response = session + "2";
    sendToServer(response.toUtf8());
}


void MainWindow::on_OutputType2Button_clicked()
{
    QString response = session + "3";
    sendToServer(response.toUtf8());
}


void MainWindow::on_PolynomInputButton_clicked()
{
    if (ui->PolynomInputA->text().isEmpty() || ui->PolynomInputRoots->text().isEmpty()) return;
    QString response = session + "4" + ui->PolynomInputA->text().trimmed() + " " + ui->PolynomInputRoots->text().trimmed();
    sendToServer(response.toUtf8());
}


void MainWindow::on_PointButton_clicked()
{
    if (ui->PolynomInputA->text().isEmpty() || ui->PolynomInputRoots->text().isEmpty() || ui->PointInput->text().isEmpty()) return;
    QString response = session + "5" + ui->PointInput->text().trimmed();
    sendToServer(response.toUtf8());
}

void MainWindow::on_RealNumbersButton_clicked()
{
    useComplexNumbers = false;
    // Отправляем команду серверу на смену типа
    QString response = session + "6" + "0"; // 0 - real numbers
    sendToServer(response.toUtf8());
}

void MainWindow::on_ComplexNumbersButton_clicked()
{
    useComplexNumbers = true;
    // Отправляем команду серверу на смену типа
    QString response = session + "6" + "1"; // 1 - complex numbers
    sendToServer(response.toUtf8());
}
