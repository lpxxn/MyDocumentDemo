QT += core gui gui-private

DEFINES += DOCX_LIBRARY

HEADERS += \
    docx_global.h \
    docxzipreader.h \
    docxzipwriter.h \
    abstractooxmlfile.h \
    abstractooxmlfileprivate.h \
    relationships.h

SOURCES += \
    docxzipreader.cpp \
    docxzipwriter.cpp \
    abstractooxmlfile.cpp \
    abstractooxmlfileprivate.cpp \
    relationships.cpp
