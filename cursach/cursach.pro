QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    boardtile.cpp \
    client.cpp \
    main.cpp \
    app.cpp \
    playerlistitem.cpp \
    server.cpp \
    serverlistitem.cpp

HEADERS += \
    app.h \
    boardtile.h \
    client.h \
    message.h \
    player.h \
    playerlistitem.h \
    server.h \
    serverlistitem.h \
    session.h \
    tile.h

FORMS += \
    app.ui \
    playerlistitem.ui \
    serverlistitem.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
