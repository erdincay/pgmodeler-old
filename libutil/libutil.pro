include(../pgmodeler.pro)

CONFIG = qt warn_on shared
QT = core gui qt3support
TEMPLATE = lib

unix {
 TARGET = util
}

windows {
 TARGET = libutil
}

DESTDIR = ../build/lib/
DEPENDPATH += ". src moc obj"
OBJECTS_DIR = obj

HEADERS += src/excecao.h \
           src/atributosglobais.h \
           src/atributosparsers.h

SOURCES += src/excecao.cpp
