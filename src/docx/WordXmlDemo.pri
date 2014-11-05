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
    docxtheme.h \
    docxfonttable.h \
    comdatafun.h \
    itagelement.h \
    docxsettings.h \
    docxwebsetting.h \
    docxstyle.h \
    docxstyleeffects.h \
    docxdocument.h

SOURCES += \
    docxzipreader.cpp \
    docxzipwriter.cpp \
    abstractooxmlfile.cpp \
    abstractooxmlfileprivate.cpp \
    relationships.cpp \
    contenttypes.cpp \
    docpropsapp.cpp \
    docpropscore.cpp \
    docxtheme.cpp \
    docxfonttable.cpp \
    comdatafun.cpp \
    itagelement.cpp \
    docxsettings.cpp \
    docxwebsetting.cpp \
    docxstyle.cpp \
    docxstyleeffects.cpp \
    docxdocument.cpp
