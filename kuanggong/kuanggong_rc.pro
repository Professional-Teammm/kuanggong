#-------------------------------------------------
#
# Project created by QtCreator 2014-12-28T14:05:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = kuanggong_rc
TEMPLATE = app


SOURCES += main.cpp\
    Item.cpp \
    mainwindow.cpp \
    map.cpp \
    mianer.cpp \
    shop.cpp

HEADERS  += \
    mainwindow.h \
    miner.h \
    item.h \
    map.h \
    shop.h

FORMS    += \
    mainwindow.ui \
    shop.ui

RESOURCES += \
    ../shopwindow/shop_image.qrc \
    ../shopwindow/shop_image.qrc \
    image.qrc \
    newimage.qrc
RC_FILE = myicon.rc

DISTFILES +=

SUBDIRS += \
    ../shopwindow/shopwindow.pro
