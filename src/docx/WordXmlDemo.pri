QT += core gui gui-private

DEFINES += DOCX_LIBRARY

HEADERS += \
    docx_global.h \
    docxzipreader.h \
    $$PWD/docxzipwriter.h

SOURCES += \
    docxzipreader.cpp \
    $$PWD/docxzipwriter.cpp
