#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , udpSocket(new QUdpSocket(this))
    , serverAddress("127.0.0.1")
    , serverPort(2040)
{
    ui->setupUi(this);
    connect(udpSocket, &QUdpSocket::readyRead, this, &MainWindow::readPendingDatagrams);
    udpSocket->bind(QHostAddress(serverAddress), serverPort);
}

MainWindow::~MainWindow()
{
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
        case 1:
        case 2:
        case 3: {
                ui->PolynomOut->setText(message);
                break;
            }
        case 4: {
                ui->OutputSolve->setText(message);
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
    QString response = "1";
    sendToServer(response.toUtf8());
}


void MainWindow::on_OutputType2Button_clicked()
{
    QString response = "2";
    sendToServer(response.toUtf8());
}


void MainWindow::on_PolynomInputButton_clicked()
{
    //inputString(ui->PolynomInputA->text(),ui->PolynomInputRoots->text(),&p);
    //ui->PolynomOut->setText(outputString(p));
    if (ui->PolynomInputA->text().isEmpty() || ui->PolynomInputRoots->text().isEmpty()) return;
    QString response = "3" + ui->PolynomInputA->text().trimmed() + " " + ui->PolynomInputRoots->text().trimmed();
    sendToServer(response.toUtf8());
}


void MainWindow::on_PointButton_clicked()
{
    //number a = p.solve(toComplex(ui->PointInput->text()));
    //ui->OutputSolve->setText("значение в точке " + ui->PointInput->text() + "  равно: " + complexOut(a));
    if (ui->PolynomInputA->text().isEmpty() || ui->PolynomInputRoots->text().isEmpty() || ui->PointInput->text().isEmpty()) return;
    QString response = "4" + ui->PointInput->text().trimmed();
    sendToServer(response.toUtf8());
}
