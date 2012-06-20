CONFIG = qt debug warn_on uitools dll
VERSION = 1
TEMPLATE = lib
TARGET = conexbd
DESTDIR = ../build/lib/
DEPENDPATH += ". src moc obj"

HEADERS += src/conexaobd.h \
           src/resultado.h

SOURCES += src/conexaobd.cpp \
           src/resultado.cpp \

OBJECTS_DIR = obj

QT += core gui qt3support

INCLUDEPATH += . \
               ../libutil/src \
               /usr/local/pgsql/include \
               /usr/include

LIBS += ../build/lib/libutil.so.1 \
        /usr/local/pgsql/lib/libpq.so
