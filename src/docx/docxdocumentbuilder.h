#ifndef DOCXDOCUMENTBUILDER_H
#define DOCXDOCUMENTBUILDER_H

#include "docx_global.h"
#include "docxfont.h"
namespace TDocx
{

class DOCX_EXPORT DocumentBuilder
{
public:
    DocumentBuilder();
    virtual ~DocumentBuilder(){}

    DocxFont& font();
    void setFont(const DocxFont &font);
    void writeln(const QString &str);
    void addParagraph() const;

private:    
    DocxFont m_font;
};
}

#endif // DOCXDOCUMENTBUILDER_H
