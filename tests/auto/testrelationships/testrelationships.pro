QT      += testlib

CONFIG  += testcase
CONFIG  += console
CONFIG  -= app_bundle


TEMPLATE = app

TARGET   = test_relationship

include(../../../DocxValue.pri)

DESTDIR = $$SOURCE_PATH/lib

INCLUDEPATH += $$SOURCE_PATH/src/docx

LIBS +=  $$SOURCE_PATH/lib/MyDocx.lib

SOURCES += \
        testrelationships.cpp \
