#ifndef DOCXDOCUMENTBUILDER_H
#define DOCXDOCUMENTBUILDER_H

#include "docx_global.h"

namespace TDocx
{
class Document;

class DOCX_EXPORT DocumentBuilder
{
public:
    DocumentBuilder(const Document* doc);
    virtual ~DocumentBuilder(){}

private:
    const Document* m_doc;
};
}

#endif // DOCXDOCUMENTBUILDER_H
