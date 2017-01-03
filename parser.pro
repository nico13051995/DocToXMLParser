#-------------------------------------------------
#
# Project created by QtCreator 2016-10-17T19:15:30
#
#-------------------------------------------------

QT       += core gui axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = parser
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    xmlbuilder.cpp \
    regexp.cpp \
    models/item.cpp \
    models/item_attribute.cpp \
    models/jsonserializable.cpp \
    selectparserwindow.cpp \
    builder.cpp \
    models/parserconfig.cpp \
    settings.cpp \
    wdconfigdialog.cpp \
    models/settingscontainer.cpp \
    models/paragraph.cpp
HEADERS  += mainwindow.h \
    xmlbuilder.h \
    regexp.h \
    models/item.h \
    models/item_attribute.h \
    models/jsonserializable.h \
    selectparserwindow.h \
    builder.h \
    models/parserconfig.h \
    settings.h \
    wdconfigdialog.h \
    models/settingscontainer.h \
    models/paragraph.h

FORMS    += mainwindow.ui \
    selectparserwindow.ui \
    wdconfigdialog.ui

CONFIG += mobility
MOBILITY = 

DESTDIR = bin
win32:QMAKE_POST_LINK += windeployqt $$OUT_PWD/$$DESTDIR
win32:RC_ICONS += xml-icon.ico

RESOURCES += \
    resources.qrc \
