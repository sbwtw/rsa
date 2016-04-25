
include(../common/common.pri)

QT       += core gui widgets network

TARGET = client
TEMPLATE = app
CONFIG += c++11 link_pkgconfig

SOURCES += main.cpp \
    clientwindow.cpp

HEADERS  += \ 
    clientwindow.h
