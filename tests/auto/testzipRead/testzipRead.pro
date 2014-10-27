QT      += testlib

CONFIG  += testcase
CONFIG  += console
CONFIG  -= app_bundle


TEMPLATE = app

TARGET   = test_read

include(../../../DocxValue.pri)

DESTDIR = $$SOURCE_PATH/lib

INCLUDEPATH += $$SOURCE_PATH/src/docx

LIBS +=  $$SOURCE_PATH/lib/MyDocx.lib

SOURCES += \
    testszipread.cpp

