QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    shopwindow.cpp

HEADERS += \
    shopwindow.h

FORMS += \
    shopwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    background.png \
    bomb.png \
    clock.png \
    clover.png \
    energy_drink.png \
    image0.png \
    image1.png \
    image2.png \
    image3.png \
    image4.png \
    image5.png \
    polish.png \
    rope.png \
    shelf.jpeg \
    shop_image/background.png \
    shop_image/bomb.png \
    shop_image/clock.png \
    shop_image/clover.png \
    shop_image/energy_drink.png \
    shop_image/polish.png \
    shop_image/rope.png \
    shop_image/shelf.jpeg \
    shop_image/tnt.png \
    tnt.png

RESOURCES += \
    shop_image.qrc
