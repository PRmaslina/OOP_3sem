#include <QCoreApplication>
#include "server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Server server;
    quint16 port = 2040; // Порт для прослушивания

    if (!server.startServer(port)) {
        qCritical() << "Failed to start server";
        return -1;
    }

    qInfo() << "UDP Server is running on port" << port;
    qInfo() << "Press Ctrl+C to stop the server";

    return a.exec();
}
