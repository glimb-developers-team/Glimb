#-------------------------------------------------
#
# Project created by QtCreator 2019-03-08T21:16:38
#
#-------------------------------------------------

QT       += core gui


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ../bin/Glimb
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

win32: LIBS += -lws2_32

INCLUDEPATH += include

SOURCES += \
        src/main.cpp \
    src/LoginWindow.cpp \
    src/RegistrationWindow.cpp \
    src/RequestFormer.cpp \
    src/LogPrinter.cpp \
    src/ServerConnector.cpp \
    src/orderwindow.cpp \
    src/ClientWindow.cpp \
    src/ConfigReader.cpp \
    src/CustomerWindow.cpp \
    src/OrderCustomerWindow.cpp


HEADERS += \
    src/RegistrationWindow.h \
    src/LoginWindow.h \
    src/RequestFormer.h \
    src/LogPrinter.h \
    src/ServerConnector.h \
    src/orderwindow.h \
    src/ClientWindow.h \
    src/ConfigReader.h \
    src/CustomerWindow.h \
    src/OrderCustomerWindow.h


FORMS += \
    form/LoginWindow.ui \
    form/RegistrationWindow.ui \
    form/orderwindow.ui \
    form/clientwindow.ui \
    form/CustomerWindow.ui \
    form/OrderCustomerWindow.ui
