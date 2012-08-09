include(../pgmodeler.pro)

CONFIG += qt warn_on
QT = core gui qt3support
VERSION = 1
TEMPLATE = lib
TARGET = parsers
DESTDIR = ../build/lib/
DEPENDPATH += ". src moc obj"
OBJECTS_DIR = obj

HEADERS += src/parseresquema.h \
           src/parserxml.h

SOURCES += src/parseresquema.cpp \
           src/parserxml.cpp

LIBS += ../build/lib/libutil.so.1
