QT       += core gui
CONFIG += c++17
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ModernBlueStyleExample
TEMPLATE = app

SOURCES += main.cpp \
    ModernBlueStyleWindow.cpp

HEADERS += \
    ModernBlueStyleWindow.h

include($$PWD/../../common.pri)
include($${SARIBBONBAR_PRI_FILE_PATH})

DESTDIR = $${SARIBBON_BIN_DIR}/bin

msvc {
    QMAKE_CFLAGS += /utf-8
    QMAKE_CXXFLAGS += /utf-8
}
