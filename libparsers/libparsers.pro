CONFIG = qt debug warn_on uitools dll
VERSION = 1
TEMPLATE = lib
TARGET = parsers
DESTDIR = ../build/lib/
DEPENDPATH += ". src moc obj"

HEADERS += src/parseresquema.h \
           src/parserxml.h

SOURCES += src/parseresquema.cpp \
           src/parserxml.cpp

OBJECTS_DIR = obj

QT += core gui qt3support

INCLUDEPATH += /usr/include/libxml2 \
               ../libutil/src \
               ../libpgmodeler/src \
               ../libparsers/src

LIBS += ../build/lib/libutil.so.1 \
       -lxml2
