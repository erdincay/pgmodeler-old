include(../pgmodeler.pro)

CONFIG = qt warn_on
QT = core gui qt3support
VERSION = 1
TEMPLATE = lib
TARGET = conexbd
DESTDIR = ../build/lib/
DEPENDPATH += ". src moc obj"
OBJECTS_DIR = obj

HEADERS += src/conexaobd.h \
           src/resultado.h

SOURCES += src/conexaobd.cpp \
           src/resultado.cpp \

LIBS += ../build/lib/libutil.so.1
