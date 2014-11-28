#include "docxxmlreader.h"
#include "docxtable.h"
#include "itagelement.h"

namespace TDocx
{
DocxXmlReader::DocxXmlReader(QIODevice *device)
{
    m_xmlReader.setDevice(device);
}

void DocxXmlReader::readStartElement()
{
    m_xmlReader.readNextStartElement();
    if (!m_xmlReader.isEndElement()) {
        if (m_xmlReader.name() == QStringLiteral("tbl")){
            //DocxTable table = new DocxTable()
        } else {
            DocxParagraph *para = new DocxParagraph();
            for (const QXmlStreamAttribute &att : m_xmlReader.attributes()) {
                para->addProperty(att.prefix().toString() + att.name().toString(), att.value().toString());
            }
        }
    }
}

void DocxXmlReader::readStartElement(DocxParagraph *parent)
{
    m_xmlReader.readNextStartElement();
    if (!m_xmlReader.isEndElement()) {
        TagElement *child = new TagElement(m_xmlReader.prefix().toString() + m_xmlReader.name().toString());

        parent->addChild(child);
    }
}

}
