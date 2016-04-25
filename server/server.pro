
include(../common/common.pri)

QT       += core gui widgets network

TARGET = server
TEMPLATE = app
CONFIG += c++11 link_pkgconfig

SOURCES += main.cpp \
    server.cpp

HEADERS  += \  
    server.h
