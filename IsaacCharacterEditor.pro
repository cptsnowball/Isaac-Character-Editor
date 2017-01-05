#-------------------------------------------------
#
# Project created by QtCreator 2015-11-23T22:17:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IsaacCharacterEditor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    character.cpp \
    draw.cpp \
    variables.cpp \
    xml.cpp \
    itemedit.cpp \
    input.cpp \
    functions.cpp \
    nameimages.cpp \
    png.cpp \
    game.cpp

HEADERS  += mainwindow.h \
    constants.h \
    character.h \
    draw.h \
    random.h \
    variables.h \
    functions.h \
    xml.h \
    itemedit.h \
    input.h \
    nameimages.h \
    png.h \
    game.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc

CONFIG += c++14

win32 {
    RC_ICONS += Resources/Icons/PurpleKey.ico
}

macx {
    ICON = Resources/Icons/PurpleKey.icns

    #The standard library isn't included properly in Mac
    #while using C++14 without this.
    QMAKE_CXXFLAGS += -stdlib=libc++
}

VERSION = 8.0.0.0
QMAKE_TARGET_COMPANY = Portal-chan
QMAKE_TARGET_PRODUCT = Isaac Character Editor
QMAKE_TARGET_DESCRIPTION =
QMAKE_TARGET_COPYRIGHT = Copyright © 2015-2017

DISTFILES += \
    Resources/Trinkets/Trinket_091.png \
    Resources/Trinkets/Trinket_093.png \
    Resources/Trinkets/Trinket_094.png \
    Resources/Trinkets/Trinket_095.png \
    Resources/Trinkets/Trinket_096.png \
    Resources/Trinkets/Trinket_097.png \
    Resources/Trinkets/Trinket_098.png \
    Resources/Trinkets/Trinket_099.png \
    Resources/Trinkets/Trinket_100.png \
    Resources/Trinkets/Trinket_101.png \
    Resources/Trinkets/Trinket_102.png \
    Resources/Trinkets/Trinket_103.png \
    Resources/Trinkets/Trinket_104.png \
    Resources/Trinkets/Trinket_105.png \
    Resources/Trinkets/Trinket_106.png \
    Resources/Trinkets/Trinket_107.png \
    Resources/Trinkets/Trinket_108.png \
    Resources/Trinkets/Trinket_109.png \
    Resources/Trinkets/Trinket_110.png \
    Resources/Trinkets/Trinket_111.png \
    Resources/Trinkets/Trinket_112.png \
    Resources/Trinkets/Trinket_113.png \
    Resources/Trinkets/Trinket_114.png \
    Resources/Trinkets/Trinket_115.png \
    Resources/Trinkets/Trinket_116.png \
    Resources/Trinkets/Trinket_117.png \
    Resources/Trinkets/Trinket_118.png \
    Resources/Trinkets/Trinket_119.png
