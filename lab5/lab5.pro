TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -L/usr/lib/ssl -lcrypto

SOURCES += \
        ioput.cpp \
        main.cpp \
        sign.cpp

HEADERS += \
    ioput.h \
    sign.h
