#include "docxparagraph.h"
#include "comdatafun.h"
#include <QFont>
#include <QXmlStreamWriter>
#include <QPair>
#include <QVector>

namespace TDocx
{

QString runAlignmentToString(const RunAlignment &format)
{
    switch (format) {
    case RunAlignment::Left : return "left"; break;
    case RunAlignment::Center : return "center"; break;
    case RunAlignment::Right : return "right"; break;
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

void DocxParagraph::addTextChild(const QString &text, const DocxFont &font)
{
    TagElement *rchild = new TagElement(QStringLiteral("w:r"));
    // font first
    if (font.isValid()){
        TagElement *fontchild = new TagElement(QStringLiteral("w:rPr"));
        fontchild->addChild(font.clone());
        rchild->addChild(fontchild);
    }
    // text second
    TagElement *textElement = new TagElement("w:t");
    textElement->setCharaters(text);
    rchild->addChild(textElement);

    addChild(rchild);
}

void DocxParagraph::addRunChild(ISaveToXml *child)
{
    TagElement *rchild = new TagElement(QStringLiteral("w:r"));
    rchild->addChild(child);
    addChild(rchild);
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

    // text
    ParagraphTagIterator iter = createIterator();

    while(iter.hasNext()) {
        // r        

        ISaveToXml *ele = iter.next();
        ele->saveToXmlElement(writer);       
    }

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

void DocxParagraph::addStyleProperty(TagElement *element)
{
    m_property.addChild(element);
}

ParagraphTagIterator DocxParagraph::createIterator() const
{
    return ParagraphTagIterator(this);
}

void DocxParagraph::setAlignment(const RunAlignment &format)
{
    if (!(int)format)
        return;
    TagElement *alignment =  new TagElement(QStringLiteral("w:jc"));
    alignment->addProperty(QStringLiteral("w:val"), runAlignmentToString(format));
    m_property.addChild(alignment);

}

}
