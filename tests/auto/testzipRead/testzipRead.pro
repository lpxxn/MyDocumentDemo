QT      += testlib

CONFIG  += testcase
CONFIG  += console
CONFIG  -= app_bundle


TEMPLATE = app

TARGET   = test_read

include(../../../DocxValue.pri)

DESTDIR = $$DOCX_TEST_APP_PATH

INCLUDEPATH += $$SOURCE_PATH/src/docx

LIBS +=  $$SOURCE_PATH/lib/MyDocx.lib

SOURCES += \
    testszipread.cpp \


