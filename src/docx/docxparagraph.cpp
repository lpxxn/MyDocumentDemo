#include "docxparagraph.h"
#include "comdatafun.h"
#include <QFont>
#include <QXmlStreamWriter>
#include <QPair>
#include <QVector>

namespace TDocx
{
DocxParagraph::DocxParagraph()
{       

}


void DocxParagraph::addProperty(QString name, QString value)
{
    m_properties.append(pairValue(name, value));
}

void DocxParagraph::addChild(TDocx::ITagElement *child)
{

}

void DocxParagraph::remoevChild(TDocx::ITagElement *child)
{
}

void DocxParagraph::saveToXmlElement(QXmlStreamWriter *writer) const
{
    writer->writeStartElement(QStringLiteral("w:p"));
    writer->writeAttribute(QStringLiteral("w:rsidR"), ComDataFun::hexNumber());

    // style
    m_property.saveToXmlElement(writer);

    // r
    writer->writeStartElement(QStringLiteral("w:r"));
    if (!m_font.family().isEmpty()){
        writer->writeStartElement(QStringLiteral("w:rPr"));
        m_font.saveToXmlElement(writer);
        writer->writeEndElement(); // end w:rPr
    }

    // text
    if (!m_text.isEmpty()) {
        writer->writeStartElement(QStringLiteral("w:t"));
        writer->writeCharacters(QString::fromUtf8(m_text.toUtf8()));
        writer->writeEndElement(); // end w:r
    }
        writer->writeEndElement(); // end w:t
    writer->writeEndElement(); // end w:p
}

DocxParagraph::~DocxParagraph()
{

}
QString DocxParagraph::text() const
{
    return m_text;
}

void DocxParagraph::setText(const QString &text)
{
    m_text = text;
}

DocxFont &DocxParagraph::font()
{
    return m_font;
}

void DocxParagraph::setFont(const DocxFont &font)
{
    m_font = font;
}

void DocxParagraph::addStyleProperty(TagElement *element)
{
    m_property.addChild(element);
}



}
