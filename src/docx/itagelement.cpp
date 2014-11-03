#include "itagelement.h"
#include <QList>

namespace TDocx
{

TagElementIterator::TagElementIterator(const ITagElement *element)
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

ITagElement::ITagElement(QString name) : m_tagName(name)
{

}

void ITagElement::addProperty(QString name, QString value)
{
    m_properties.append(pairValue(name, value));
}

ITagElement::~ITagElement()
{
    TagElementIterator iter =  createIterator();
    while(iter.hasNext()) {
        ITagElement *ele = iter.next();
        delete ele;
    }
    m_childs.clear();
}

void ITagElement::addChild(ITagElement *child)
{
    m_childs.append(child);
}

void ITagElement::remoevChild(ITagElement *child)
{
    if (m_childs.contains(child)) {
        m_childs.removeOne(child);
        delete child;
        child = nullptr;
    }
}

void ITagElement::saveToXmlElement(QXmlStreamWriter *writer) const
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

TagElementIterator ITagElement::createIterator() const
{
    return  TagElementIterator(this);
}

}





