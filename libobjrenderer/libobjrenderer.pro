include(../pgmodeler.pro)

CONFIG = qt warn_on uitools shared
QT = core gui qt3support
TEMPLATE = lib

unix {
 TARGET = objrenderer
}

windows {
 TARGET = libobjrenderer
}

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

LIBS += ../build/lib/libutil.$${LIB_SUFFIX} \
        ../build/lib/libparsers.$${LIB_SUFFIX} \
        ../build/lib/libpgmodeler.$${LIB_SUFFIX}
