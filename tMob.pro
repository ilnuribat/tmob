#-------------------------------------------------
#
# Project created by QtCreator 2014-05-06T17:45:50
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tMob
TEMPLATE = app


SOURCES += main.cpp\
    welcome.cpp \
    registration.cpp \
    table.cpp \
    extern_vars.cpp

HEADERS  += \
    welcome.h \
    registration.h \
    table.h \
    extern_vars.h

FORMS    += \
    welcome.ui \
    registration.ui \
    table.ui

CONFIG += mobility
MOBILITY = 

RESOURCES += \
    qres.qrc

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

OTHER_FILES += \
    android/AndroidManifest.xml

