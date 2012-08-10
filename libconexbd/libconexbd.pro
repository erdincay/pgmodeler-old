include(../pgmodeler.pro)

CONFIG = qt warn_on shared
QT = core gui qt3support
TEMPLATE = lib

unix {
 TARGET = conexbd
}

windows {
 TARGET = libconexbd
}

DESTDIR = ../build/lib/
DEPENDPATH += ". src moc obj"
OBJECTS_DIR = obj

HEADERS += src/conexaobd.h \
           src/resultado.h

SOURCES += src/conexaobd.cpp \
           src/resultado.cpp \

LIBS += ../build/lib/libutil.$${LIB_SUFFIX}
