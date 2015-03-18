# Location of MapMaker
MM_PREFIX = /home/yb/prog/mapmaker/mapmaker

# Project configuration
unix: LIBS += -L$$MM_PREFIX/lib -lmm0
INCLUDEPATH += $$MM_PREFIX/include

QT += core gui concurrent
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 depend_includepath
TEMPLATE = app
TARGET = mmgui

HEADERS += $$files(src/*.hpp)
SOURCES += $$files(src/*.cpp)
FORMS   += $$files(forms/*.ui)

OTHER_FILES += LICENSE README.md
