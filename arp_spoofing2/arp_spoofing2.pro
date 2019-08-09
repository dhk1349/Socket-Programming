TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        packet_function.cpp \
        protocol_class.cpp

HEADERS += \
    packet_function.h \
    protocol_class.h
