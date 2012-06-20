CONFIG = qt debug warn_on uitools dll
VERSION = 1
TEMPLATE = lib
TARGET = util
DESTDIR = ../build/lib/
DEPENDPATH += ". src moc obj"

HEADERS += src/excecao.h \
           src/atributosglobais.h \
           src/atributosparsers.h

SOURCES += src/excecao.cpp

OBJECTS_DIR = obj

QT += core gui qt3support

INCLUDEPATH += src \
               /usr/include
