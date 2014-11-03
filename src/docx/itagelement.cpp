#include "itagelement.h"
#include <QList>
namespace TDocx
{

ITagElement::ITagElement(QString name) : m_tagName(name)
{

}

void ITagElement::addProperty(QString name, QString value)
{
    m_properties.append(pairValue(name, value));
}

void ITagElement::addChild(ITagElement *child)
{
    m_childs.append(child);
}

void ITagElement::remoevChild(ITagElement *child)
{
    if (m_childs.contains(child)) {
        m_childs.removeOne(child);
    }
}


bool ITagElement::hasNext() const
{
    return m_childs.count() > 0 && m_currentIndex < m_childs.size();
}

ITagElement *ITagElement::next() const
{
    return m_childs.at(m_currentIndex++);
}

void ITagElement::saveToXmlElement(QXmlStreamWriter *writer) const
{
    writer->writeStartElement(m_tagName);
    if (m_properties.count() > 0)
        for (pairValue att : m_properties) {
            writer->writeAttribute(att.first, att.second);
        }
    while(hasNext()) {
       ITagElement *element = next();
       element->saveToXmlElement(writer);
    }
    writer->writeEndElement();
}

}


