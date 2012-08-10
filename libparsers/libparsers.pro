include(../pgmodeler.pro)

CONFIG += qt warn_on shared
QT = core gui qt3support

TEMPLATE = lib

unix {
 TARGET = parsers
}

windows {
 TARGET = libparsers
}

DESTDIR = ../build/lib/
DEPENDPATH += ". src moc obj"
OBJECTS_DIR = obj

HEADERS += src/parseresquema.h \
           src/parserxml.h

SOURCES += src/parseresquema.cpp \
           src/parserxml.cpp

LIBS += ../build/lib/libutil.$${LIB_SUFFIX}
