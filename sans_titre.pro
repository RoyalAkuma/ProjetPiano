#-------------------------------------------------
#
# Project created by QtCreator 2016-03-14T14:15:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

TARGET = sans_titre
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    note.cpp \
    partition.cpp \
    factorynote.cpp

HEADERS  += mainwindow.h \
    note.h \
    partition.h \
    factorynote.h

FORMS    += mainwindow.ui

DISTFILES += \
    ../../Desktop/IHM/socle.png

RESOURCES += \
    ressources/ressources.qrc
