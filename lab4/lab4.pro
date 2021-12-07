TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        iobytes.cpp \
        main.cpp \
        rsa.cpp \
        rsagenerator.cpp

HEADERS += \
    iobytes.h \
    rsa.h \
    rsagenerator.h
