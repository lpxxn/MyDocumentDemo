QT      += testlib

CONFIG  += testcase \
           console
CONFIG  -= app_bundle


TEMPLATE = app

TARGET   = test_read

#INCLUDEPATH += ../../../src/docx
#message($$SOURCE_PATH/src)

SOURCES += \
    testszipread.cpp

