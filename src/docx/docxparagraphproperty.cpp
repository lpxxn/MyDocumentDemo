#include "docxparagraphproperty.h"

#include <QXmlStreamWriter>

namespace TDocx
{
const QString strPrp = QStringLiteral("w:pPr");

ParPropertyIterator::ParPropertyIterator(const DocxParagraphProperty *paragraph)
    : m_paragraph(paragraph), m_currentIndex(0)
{

}

bool ParPropertyIterator::hasNext() const
{
    return m_paragraph->m_childs.count() > 0 && m_currentIndex < m_paragraph->m_childs.size();
}

ISaveToXml *ParPropertyIterator::next() const
{
    return m_paragraph->m_childs.at(m_currentIndex++);
}

// end ParPropertyIterator


// DocxParagraphProperty

DocxParagraphProperty::DocxParagraphProperty()
{
}

DocxParagraphProperty::~DocxParagraphProperty()
{
    ParPropertyIterator iter =  createIterator();
    while(iter.hasNext()) {
        ISaveToXml *ele = iter.next();
        delete ele;
    }
    m_childs.clear();
}

QString DocxParagraphProperty::name() const
{
    return strPrp;
}

void DocxParagraphProperty::addProperty(QString name, QString value)
{
    m_properties.append(pairValue(name, value));
}

void DocxParagraphProperty::addChild(ISaveToXml *child)
{
    m_childs.append(child);
}

void DocxParagraphProperty::remoevChild(TDocx::ISaveToXml *child)
{
    if (m_childs.contains(child)) {
        m_childs.removeOne(child);
        delete child;
        child = nullptr;
    }
}

void DocxParagraphProperty::setIsRead(bool isread)
{
    m_isread = isread;
}

void DocxParagraphProperty::saveToXmlElement(QXmlStreamWriter *writer) const
{
    if (m_childs.isEmpty())
        return;
    if (!m_isread) {
        writer->writeStartElement(strPrp);
        for (const pairValue &att : m_properties) {
            writer->writeAttribute(att.first, att.second);
        }
    }
    ParPropertyIterator iter = createIterator();
    while(iter.hasNext()) {
        ISaveToXml *e = iter.next();
        e->saveToXmlElement(writer);
    }
    if (!m_isread)
        writer->writeEndElement();
}

ParPropertyIterator DocxParagraphProperty::createIterator() const
{
    return ParPropertyIterator(this);
}

}


