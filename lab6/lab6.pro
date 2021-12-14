TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        huffman.cpp \
        inbytes.cpp \
        iofrequency.cpp \
        main.cpp \
        outbytes.cpp \
        treenode.cpp

HEADERS += \
    huffman.h \
    inbytes.h \
    outbytes.h \
    treenode.h
