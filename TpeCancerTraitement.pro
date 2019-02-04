#-------------------------------------------------
#
# Project created by QtCreator 2019-01-29T17:09:59
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TpeCancerTraitement
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS #WITH_CODECS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        app.cpp \
        playvideo.cpp \
        Class/butmanager.cpp \
        Class/buttonoverlay.cpp

HEADERS += \
        app.h \
        playvideo.h \
        medias.h \
        Class/butmanager.h \
        Class/buttonoverlay.h

FORMS += \
        app.ui \
        playvideo.ui

unix {
    isEmpty(PREFIX):PREFIX = /usr
    BINDIR = $$PREFIX/bin
    DATADIR = $$PREFIX/share

    target.path = $$BINDIR
    icon.path = $$DATADIR/icons/hicolor/scalable/apps
    desktop.path = $$DATADIR/applications

    icon.files += Images/icon.svg
    desktop.files += qastrologer.desktop
    INSTALLS += target icon desktop
}
RC_FILE = icon.rc

contains(DEFINES, WITH_CODECS) {

RESOURCES += \
        ressources-codec.qrc

message("Compilation avec Codecs.")
}else{

RESOURCES += \
        ressources.qrc

message("Compilation sans Codecs.")
}
