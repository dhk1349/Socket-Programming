TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lpcap
SOURCES += \
        header_class.cpp \
        main.cpp

HEADERS += \
    header_class.h \
    packet_structure.h
