 CONFIG = qt debug \
 warn_on \
 uitools
TEMPLATE = app
TARGET = test-objrenderer
DEPENDPATH += ". src ui moc obj"

FORMS += ui/formprincipal.ui

HEADERS += src/formprincipal.h \
           src/aplicacao.h \
    src/ui_formprincipal.h

SOURCES += src/formprincipal.cpp \
           src/main.cpp

MOC_DIR = moc
OBJECTS_DIR = obj
UI_DIR = ui
UI_HEADERS_DIR  = src
UI_SOURCES_DIR  = src

QT += core \
gui \
qt3support
DESTDIR = ../../build

INCLUDEPATH += . \
src \
../../libutil/src \
../../libpgmodeler/src \
../../libparsers/src \
../../libconexbd/src \
../../libobjrenderer/src \
/usr/include/libxml2


LIBS += ../../build/lib/libobjrenderer.so.1 \
        ../../build/lib/libutil.so.1 \
        ../../build/lib/libpgmodeler.so.1 \
        ../../build/lib/libparsers.so.1 \
        -lxml2
