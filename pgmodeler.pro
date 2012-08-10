unix {
 GLOBAL_INCLUDES = .\
                   /usr/local/pgsql/include \
                   /usr/include \
                   /usr/include/libxml2


 GLOBAL_LIBS =  /usr/local/pgsql/lib/libpq.so \
                -lxml2

 LIB_SUFFIX = so.1.0.0

}

windows {
 GLOBAL_INCLUDES = .\
                   "C:/Program Files (x86)/PostgreSQL/9.1/include/" \
                   "C:/libxml2/include/"

 GLOBAL_LIBS = "C:/Program Files (x86)/PostgreSQL/9.1/lib/libpq.dll" \
               "C:/libxml2/bin/libxml2.dll"

 LIB_SUFFIX = dll
}

INCLUDEPATH = $${GLOBAL_INCLUDES} \
              $$PWD/libutil/src \
              $$PWD/libconexbd/src \
              $$PWD/libparsers/src \
              $$PWD/libpgmodeler/src \
              $$PWD/libobjrenderer/src \
              $$PWD/pgmodeler_ui/src

LIBS = $${GLOBAL_LIBS}


TEMPLATE = subdirs
SUBDIRS = libutil \
          libconexbd \
          libparsers \
          libpgmodeler \
          libobjrenderer \
          pgmodeler_ui

sources.files = models schemas lang conf
sources.path = .
INSTALLS += sources
