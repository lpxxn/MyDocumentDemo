#include "docxdocumentbuilder.h"
#include "docxdocument.h"

namespace TDocx
{
DocumentBuilder::DocumentBuilder(const Document *doc)    
{
    //m_doc = doc;
}
DocxFont& DocumentBuilder::font()
{
    return m_font;
}

void DocumentBuilder::setFont(const DocxFont &font)
{
    m_font = font;
}

void DocumentBuilder::writeln(const QString &str)
{

}

void DocumentBuilder::addParagraph() const
{
    //m_doc->addParagraph();
}

}
