#-------------------------------------------------
#
# Project created by QtCreator 2016-10-21T13:33:42
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Shadows
TEMPLATE = app

#LIBS += -lOpenGL32

SOURCES += main.cpp\
        mainwindow.cpp \
    scene.cpp \
    loader.cpp \
    object.cpp \
    camera.cpp

HEADERS  += mainwindow.h \
    scene.h \
    loader.h \
    object.h \
    camera.h

FORMS    += mainwindow.ui

RESOURCES += \
    shaders.qrc
