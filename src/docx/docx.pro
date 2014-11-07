include(../../docxvalue.pri)
include(wordxmldemo.pri)


TARGET = $$LIBNAME


TEMPLATE = lib
DESTDIR = $$DOCX_LIB_PATH

FILES_COPY_SRC = $$DOCX_LIB_PATH/


$$copyFile($$FILES_COPY_SRC, $$DOCX_TEST_APP_PATH)





