QT += core gui gui-private

DEFINES += DOCX_LIBRARY

HEADERS += \
    docx_global.h \
    docxzipreader.h \
    docxzipwriter.h \
    abstractooxmlfile.h \
    abstractooxmlfileprivate.h \
    relationships.h \
    contenttypes.h \
    docpropsapp.h \
    docpropscore.h \
    docxtheme.h

SOURCES += \
    docxzipreader.cpp \
    docxzipwriter.cpp \
    abstractooxmlfile.cpp \
    abstractooxmlfileprivate.cpp \
    relationships.cpp \
    contenttypes.cpp \
    docpropsapp.cpp \
    docpropscore.cpp \
    docxtheme.cpp
