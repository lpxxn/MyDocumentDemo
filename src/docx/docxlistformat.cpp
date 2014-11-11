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

void DocxListFormat::saveToXmlElement(QXmlStreamWriter *writer) const
{

}


DocxListFormat::~DocxListFormat()
{

}


}




