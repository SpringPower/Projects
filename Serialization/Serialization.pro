TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

HEADERS += \
    serialization.hpp

QMAKE_CXXFLAGS += -std=c++11
