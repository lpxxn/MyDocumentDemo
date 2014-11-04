#include "itagelement.h"
#include <QList>

namespace TDocx
{

TagElementIterator::TagElementIterator(const TagElement *element)
    :m_tagElement(element),m_currentIndex(0)
{

}

bool TagElementIterator::hasNext() const
{
    return m_tagElement->m_childs.count() > 0 && m_currentIndex < m_tagElement->m_childs.size();
}

ITagElement *TagElementIterator::next() const
{
    return m_tagElement->m_childs.at(m_currentIndex++);
}

TagElement::TagElement(const QString &name) : m_tagName(name)
{

}

void TagElement::addProperty(QString name, QString value)
{
    m_properties.append(pairValue(name, value));
}

TagElement::~TagElement()
{
    TagElementIterator iter =  createIterator();
    while(iter.hasNext()) {
        ITagElement *ele = iter.next();
        delete ele;
    }
    m_childs.clear();
}

void TagElement::addChild(ITagElement *child)
{
    m_childs.append(child);
}

void TagElement::remoevChild(ITagElement *child)
{
    if (m_childs.contains(child)) {
        m_childs.removeOne(child);
        delete child;
        child = nullptr;
    }
}

void TagElement::saveToXmlElement(QXmlStreamWriter *writer) const
{
    writer->writeStartElement(m_tagName);
    if (m_properties.count() > 0)
        for (pairValue att : m_properties) {
            writer->writeAttribute(att.first, att.second);
        }
    TagElementIterator iter =  createIterator();
    while(iter.hasNext()) {
        ITagElement *element = iter.next();
        element->saveToXmlElement(writer);
    }
    writer->writeEndElement();
}

TagElementIterator TagElement::createIterator() const
{
    return  TagElementIterator(this);
}

}





