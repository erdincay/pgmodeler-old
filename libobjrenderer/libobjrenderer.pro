include(../pgmodeler.pro)

CONFIG = qt warn_on uitools
QT = core gui qt3support

VERSION = 1
TEMPLATE = lib
TARGET = objrenderer
DESTDIR = ../build/lib/
DEPENDPATH += ". src moc obj"
OBJECTS_DIR = obj
MOC_DIR = moc

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

LIBS += ../build/lib/libutil.so.1 \
        ../build/lib/libparsers.so.1 \
        ../build/lib/libpgmodeler.so.1
