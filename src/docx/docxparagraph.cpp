#include "docxparagraph.h"
#include "comdatafun.h"
#include <QFont>
#include <QXmlStreamWriter>
#include <QPair>
#include <QVector>

namespace TDocx
{

QString RunAligmentToString(const RunAligment &format)
{
    switch (format) {
    case RunAligment::Left : return "left"; break;
    case RunAligment::Center : return "center"; break;
    case RunAligment::Right : return "right"; break;
    default : return "left"; break;
    }
}

ParagraphTagIterator::ParagraphTagIterator(const DocxParagraph *element)
    : m_currentIndex(0), m_paragraph(element)
{

}

bool ParagraphTagIterator::hasNext() const
{
    return m_paragraph->m_childs.count() > 0 && m_currentIndex < m_paragraph->m_childs.size();
}

ISaveToXml *ParagraphTagIterator::next() const
{
    return m_paragraph->m_childs.at(m_currentIndex++);
}

// begin DocxParagraph
DocxParagraph::DocxParagraph()
{       

}

void DocxParagraph::addProperty(QString name, QString value)
{
    m_properties.append(pairValue(name, value));
}

void DocxParagraph::addChild(TDocx::ISaveToXml *child)
{
    m_childs.append(child);
}

void DocxParagraph::remoevChild(ISaveToXml *child)
{
    if (m_childs.contains(child)) {
        m_childs.removeOne(child);
        delete child;
        child = nullptr;
    }
}


void DocxParagraph::saveToXmlElement(QXmlStreamWriter *writer) const
{
    writer->writeStartElement(QStringLiteral("w:p"));
    writer->writeAttribute(QStringLiteral("w:rsidR"), ComDataFun::hexNumber());

    for (const pairValue &att : m_properties) {
        writer->writeAttribute(att.first, att.second);
    }

    // style
    m_property.saveToXmlElement(writer);

    // r
    writer->writeStartElement(QStringLiteral("w:r"));

    if (!m_font.family().isEmpty()){
        writer->writeStartElement(QStringLiteral("w:rPr"));
        m_font.saveToXmlElement(writer);
        writer->writeEndElement(); // end w:rPr
    }

    ParagraphTagIterator iter = createIterator();
    // text
    while(iter.hasNext()) {
        ISaveToXml *ele = iter.next();
        ele->saveToXmlElement(writer);
    }

    writer->writeEndElement(); // end w:t
    writer->writeEndElement(); // end w:p
}

DocxParagraph::~DocxParagraph()
{
    ParagraphTagIterator iter =  createIterator();
    while(iter.hasNext()) {
        ISaveToXml *ele = iter.next();
        delete ele;
    }
    m_childs.clear();
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
    addChild(element);
}

ParagraphTagIterator DocxParagraph::createIterator() const
{
    return ParagraphTagIterator(this);
}

void DocxParagraph::paragraphAligment(const RunAligment &format)
{
    if (!(int)format)
        return;
    TagElement *aligment =  new TagElement(QStringLiteral("w:jc"));
    aligment->addProperty(QStringLiteral("w:val"), RunAligmentToString(format));
    m_property.addChild(aligment);

}


}
