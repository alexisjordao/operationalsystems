QT += core
QT -= gui

TARGET = trabalhoDois
CONFIG += console
CONFIG -= app_bundle
CONFIG += c++11

TEMPLATE = app

SOURCES += main.cpp \
    ../../BlackLib/v3_0/BlackGPIO/BlackGPIO.cpp \
    ../../BlackLib/v3_0/BlackCore.cpp

HEADERS += \
    ../../BlackLib/v3_0/BlackGPIO/BlackGPIO.h \
    ../../BlackLib/v3_0/BlackLib.h \
    ../../BlackLib/v3_0/BlackErr.h \
    ../../BlackLib/v3_0/BlackDef.h \
    ../../BlackLib/v3_0/BlackCore.h

