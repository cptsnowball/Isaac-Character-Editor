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
    random.cpp \
    variables.cpp \
    xml.cpp

HEADERS  += mainwindow.h \
    constants.h \
    character.h \
    draw.h \
    random.h \
    variables.h \
    functions.h \
    xml.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc

CONFIG += c++14

macx {
    #The standard library isn't included properly in Mac
    #while using C++14 without this.
    QMAKE_CXXFLAGS += -stdlib=libc++
}

VERSION = 6.0.0.0
QMAKE_TARGET_COMPANY = Portal-chan
QMAKE_TARGET_PRODUCT = Isaac Character Editor
QMAKE_TARGET_DESCRIPTION =
QMAKE_TARGET_COPYRIGHT = Copyright © 2015-2016
