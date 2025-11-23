#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QVector>
#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QDebug>
#include <QDateTime>
#include "polynom.h"
#include "complex.h"

enum NumberType {
    REAL_NUMBERS,
    COMPLEX_NUMBERS
};

struct Session{
    QString id;
    NumberType numberType;

    // Указатели на полиморфные полиномы
    Polynom<double>* realPoly;
    Polynom<TComplex>* complexPoly;

    Session(QString _id, NumberType type) {
        id = _id;
        numberType = type;
        if (type == REAL_NUMBERS) {
            realPoly = new Polynom<double>();
            complexPoly = nullptr;
        } else {
            complexPoly = new Polynom<TComplex>();
            realPoly = nullptr;
        }
    }

    ~Session() {
        delete realPoly;
        delete complexPoly;
    }

    // Универсальные методы доступа
    QString getOutputString() {
        if (numberType == REAL_NUMBERS) {
            return outputString(*realPoly);
        } else {
            return outputString(*complexPoly);
        }
    }

    void setPrintType(int type) {
        if (numberType == REAL_NUMBERS) {
            realPoly->setPrintType(type);
        } else {
            complexPoly->setPrintType(type);
        }
    }

    void updatePolynom(QString aText, QString rootsText) {
        if (numberType == REAL_NUMBERS) {
            inputString(aText, rootsText, realPoly);
        } else {
            inputString(aText, rootsText, complexPoly);
        }
    }

    QString solveAtPoint(QString point) {
        if (numberType == REAL_NUMBERS) {
            double x = point.toDouble();
            double result = realPoly->solve(x);
            return QString::number(result);
        } else {
            TComplex x = toComplex(point);
            TComplex result = complexPoly->solve(x);
            return complexOut(result);
        }
    }
};

class Server : public QObject
{
    Q_OBJECT

public:
    explicit Server(QObject *parent = nullptr);
    ~Server();

    bool startServer(quint16 port);
    void stopServer();

private slots:
    void readPendingDatagrams();
    void processDatagram(const QNetworkDatagram &datagram);

private:
    QVector<Session*> sessions;
    QUdpSocket *m_udpSocket;
    quint16 m_port;
    bool m_isRunning;
    QByteArray processMessage(const QByteArray &data);
};

#endif // SERVER_H
