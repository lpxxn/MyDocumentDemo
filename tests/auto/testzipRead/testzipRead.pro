QT      += testlib
QT      += core

CONFIG  += testcase
CONFIG  += console
CONFIG  -= app_bundle


TEMPLATE = app

TARGET   = test_read

include(../../../DocxValue.pri)

DESTDIR = $$SOURCE_PATH/lib
#INCLUDEPATH += "D:/QtCode/QTCODEDEMO/MyDocumentDemo/src/docx"
INCLUDEPATH += $$SOURCE_PATH/src/docx
message("$$INCLUDEPATH")

#LIBS += D:/QtCode/QTCODEDEMO/MyDocumentDemo/lib/MyDocx.lib#-lMyDocx
LIBS +=  $$SOURCE_PATH/lib/MyDocx.lib

SOURCES += \
    testszipread.cpp

