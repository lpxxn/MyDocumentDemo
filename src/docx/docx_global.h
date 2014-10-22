#ifndef DOCXGLOBAL_H
#define DOCXGLOBAL_H

#include <QtCore/qglobal.h>
#if defined(DOCX_LIBRARY)
#  define DOCX_EXPORT Q_DECL_EXPORT
#else
#  define DOCX_EXPORT Q_DECL_IMPORT
#endif

#endif // DOCXGLOBAL_H
