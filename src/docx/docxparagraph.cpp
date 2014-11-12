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

void DocxParagraph::addChild(TDocx::ISaveToXml *child)
{

}

void DocxParagraph::remoevChild(ISaveToXml *child)
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
    for (const TagElement *eles : m_contentElement) {
        eles->saveToXmlElement(writer);
    }
        writer->writeEndElement(); // end w:t
    writer->writeEndElement(); // end w:p
}

DocxParagraph::~DocxParagraph()
{

}


void DocxParagraph::setText(const QString &text)
{
    TagElement *textElement = new TagElement("w:t");
    textElement->addCharaters(text);
    addContentElement(textElement);
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

void DocxParagraph::addContentElement(TagElement *element)
{
    m_contentElement.append(element);
}


}
