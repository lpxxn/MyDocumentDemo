QT      += testlib core

CONFIG  += testcase
CONFIG  += console
CONFIG  -= app_bundle

TEMPLATE = app

DESTDIR = $$DOCX_TEST_APP_PATH

INCLUDEPATH += $$SOURCE_PATH/src/docx

#LIBS +=  $$SOURCE_PATH/lib/MyDocx.lib

LIBS += -L$$DESTDIR/ -l$$LIBNAME
