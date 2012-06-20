CONFIG = qt debug warn_on uitools dll
VERSION = 1
TEMPLATE = lib
TARGET = objrenderer
DESTDIR = ../build/lib/
DEPENDPATH += ". src moc obj"
OBJECTS_DIR = obj
MOC_DIR = moc

QT += core gui svg qt3support

INCLUDEPATH += . \
               /usr/include/libxml2 \
               ../libutil/src \
               ../libparsers/src \
               ../libpgmodeler/src \
               /usr/include

LIBS += ../build/lib/libutil.so.1 \
        ../build/lib/libparsers.so.1 \
        ../build/lib/libpgmodeler.so.1

HEADERS +=  src/objetografico.h \
            src/ogcaixatexto.h \
            src/ogtabela.h \
            src/ogvisao.h \
            src/ogrelacionamento.h \
            src/ogtituloobjeto.h \
            src/ogsubitemobjeto.h \
            src/ogtabelabase.h \
            src/cenaobjetos.h

SOURCES +=  src/objetografico.cpp \
            src/ogcaixatexto.cpp \
            src/ogtabela.cpp \
            src/ogvisao.cpp \
            src/ogrelacionamento.cpp \
            src/ogtituloobjeto.cpp \
            src/ogsubitemobjeto.cpp \
            src/ogtabelabase.cpp \
            src/cenaobjetos.cpp
