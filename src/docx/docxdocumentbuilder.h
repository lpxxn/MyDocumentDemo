#ifndef DOCXDOCUMENTBUILDER_H
#define DOCXDOCUMENTBUILDER_H

#include "docx_global.h"
#include "docxfont.h"
namespace TDocx
{
class Document;

class DOCX_EXPORT DocumentBuilder
{
public:
    DocumentBuilder(const Document* doc);
    virtual ~DocumentBuilder(){}

    DocxFont& font();
    void setFont(const DocxFont &font);
    void writeln(const QString &str);
    void addParagraph() const;

private:
    //Document* m_doc;
    DocxFont m_font;
};
}

#endif // DOCXDOCUMENTBUILDER_H
