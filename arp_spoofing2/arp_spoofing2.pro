TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS+= -lpcap
SOURCES += \
        main.cpp \
        protocol_class.cpp

HEADERS += \
    protocol_class.h
