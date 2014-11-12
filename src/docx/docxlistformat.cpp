#include "docxlistformat.h"
#include <QXmlStreamWriter>

namespace TDocx
{


DocxListFormat::DocxListFormat()
{
}

DocxListFormat::DocxListFormat(const ListFormatStyle &listStyle)
    : m_flag(listStyle)
{

}


DocxListFormat::~DocxListFormat()
{

}
DocxFont DocxListFormat::font() const
{
    return m_font;
}

void DocxListFormat::setFont(const DocxFont &font)
{
    m_font = font;
}
ListFormatStyle DocxListFormat::flag() const
{
    return m_flag;
}

void DocxListFormat::setFlag(const ListFormatStyle &flag)
{
    m_flag = flag;
}




}




