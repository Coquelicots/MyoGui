#-------------------------------------------------
#
# Project created by QtCreator 2016-12-26T22:40:46
#
#-------------------------------------------------

QT+= core gui
QT+= multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyoGui
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        myogui.cpp \
    MyoSensor.cpp \
    camerawidget.cpp \
    glwidget.cpp \
    videowidget.cpp \
    audiowidget.cpp

HEADERS  += myogui.h \
    MyoSensor.h \
    camerawidget.h \
    glwidget.h \
    videowidget.h \
    audiowidget.h

FORMS    += myogui.ui

mac: LIBS += -F$$PWD/Myo-sdk/ -framework myo
else:unix: LIBS += -L$$PWD/Myo-sdk/ -lmyo
QMAKE_CXXFLAGS+=-F$$PWD/Myo-sdk/
QMAKE_LFLAGS_SONAME  = -Wl,-myo,$$PWD/Myo-sdk/
