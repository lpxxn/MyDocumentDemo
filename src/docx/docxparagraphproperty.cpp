#include "docxparagraphproperty.h"

#include <QXmlStreamWriter>

namespace TDocx
{

ParPropertyIterator::ParPropertyIterator(const DocxParagraphProperty *paragraph)
    : m_paragraph(paragraph), m_currentIndex(0)
{

}

bool ParPropertyIterator::hasNext() const
{
    return m_paragraph->m_childs.count() > 0 && m_currentIndex < m_paragraph->m_childs.size();
}

ITagElement *ParPropertyIterator::next() const
{
    return m_paragraph->m_childs.at(m_currentIndex++);
}

// end ParPropertyIterator


// DocxParagraphProperty

DocxParagraphProperty::DocxParagraphProperty()
{
}

void DocxParagraphProperty::addProperty(QString name, QString value)
{
    m_properties.append(pairValue(name, value));
}

void DocxParagraphProperty::addChild(TDocx::ITagElement *child)
{
    m_childs.append(child);
}

void DocxParagraphProperty::remoevChild(TDocx::ITagElement *child)
{
    if (m_childs.contains(child)) {
        m_childs.removeOne(child);
        delete child;
        child = nullptr;
    }
}

void DocxParagraphProperty::saveToXmlElement(QXmlStreamWriter *writer) const
{
    if (m_childs.isEmpty())
        return;
    writer->writeStartElement("w:pPr");
    for (const pairValue &att : m_properties) {
        writer->writeAttribute(att.first, att.second);
    }
    ParPropertyIterator iter = createIterator();
    while(iter.hasNext()) {
        ITagElement *e = iter.next();
        e->saveToXmlElement(writer);
    }
    writer->writeEndElement();
}

ParPropertyIterator DocxParagraphProperty::createIterator() const
{
    return ParPropertyIterator(this);
}

}


