include(../pgmodeler.pro)

CONFIG = qt warn_on
QT = core gui qt3support

VERSION = 1
TEMPLATE = lib
TARGET = util
DESTDIR = ../build/lib/
DEPENDPATH += ". src moc obj"
OBJECTS_DIR = obj

HEADERS += src/excecao.h \
           src/atributosglobais.h \
           src/atributosparsers.h

SOURCES += src/excecao.cpp
