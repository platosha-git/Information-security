TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        aes.cpp \
        aescoder.cpp \
        aesdecoder.cpp \
        invaes.cpp \
        main.cpp

HEADERS += \
    aescoder.h \
    tables.h
