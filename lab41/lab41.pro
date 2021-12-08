TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        inbytes.cpp \
        main.cpp \
        outbytes.cpp \
        rsa.cpp \
        rsagenerator.cpp

HEADERS += \
    inbytes.h \
    outbytes.h \
    rsa.h \
    rsagenerator.h
