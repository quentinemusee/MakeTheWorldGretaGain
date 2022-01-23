QT       += core gui multimedia multimediawidgets testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 resources_big

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    background.cpp \
    bullet.cpp \
    explosion.cpp \
    greta.cpp \
    ingamescene.cpp \
    main.cpp \
    mainwindow.cpp \
    nuclearbomb.cpp \
    platform.cpp \
    poopbullet.cpp \
    trumpet.cpp \
    trumpetcac.cpp \
    trumpetdis.cpp

HEADERS += \
    background.h \
    bullet.h \
    character.h \
    entity.h \
    explosion.h \
    greta.h \
    ingamescene.h \
    mainwindow.h \
    nuclearbomb.h \
    platform.h \
    poopbullet.h \
    trumpet.h \
    trumpetcac.h \
    trumpetdis.h \
    update.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ressources.qrc
