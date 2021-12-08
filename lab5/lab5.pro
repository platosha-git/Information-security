TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -L/usr/lib/ssl -lcrypto

SOURCES += \
        main.cpp \
        sign.cpp

HEADERS += \
    sign.h
