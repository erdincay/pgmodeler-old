CONFIG = qt debugwarn_on uitools ordered

TEMPLATE = subdirs

SUBDIRS = libutil \
          libconexbd \
          libparsers \
          libpgmodeler \
          libobjrenderer \
          pgmodeler_ui

QT += core gui qt3support

INCLUDEPATH += . \
               libutil/src \
               libconexbd/src \
               libpgmodeler/src \
               libparsers/src \
               libobjrenderer/src \
               pgmodeler_ui/src \
               /usr/include

TRANSLATIONS += i18n/pgsqldbm-en_US.ts

CODECFORTR = UTF-8

sources.files = models schemas lang conf
sources.path = .
INSTALLS += sources
