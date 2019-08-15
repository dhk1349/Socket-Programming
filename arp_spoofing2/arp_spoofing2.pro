TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS+= -lpcap
SOURCES += \
        header.cpp \
        main.cpp \
        protocol_class.cpp

HEADERS += \
    header.h \
    protocol_class.h
