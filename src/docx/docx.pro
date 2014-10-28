LIBNAME = MyDocx
TARGET = $$LIBNAME

include(WordXmlDemo.pri)
include(../../DocxValue.pri)

TEMPLATE = lib
DESTDIR = $$DOCX_LIB_PATH

FILES_COPY_SRC = $$DOCX_LIB_PATH/


$$copyFile($$FILES_COPY_SRC, $$DOCX_TEST_APP_PATH)




