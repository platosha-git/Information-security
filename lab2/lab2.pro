TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        enigma.cpp \
        iohandlers.cpp \
        main.cpp \
        reflector.cpp \
        rotor.cpp

HEADERS += \
    enigma.h \
    iohandlers.h \
    reflector.h \
    rotor.h
