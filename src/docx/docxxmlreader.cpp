#include "docxxmlreader.h"
#include "docxtable.h"
#include "itagelement.h"

#include <QBuffer>
#include <QDebug>

namespace TDocx
{
const QString strcolon = QStringLiteral(":");
const QString strParagraph = QStringLiteral("p");
const QString strRun = QStringLiteral("r");

DocxXmlReader::DocxXmlReader(QIODevice *device)
{
    m_xmlReader.setDevice(device);
}


void DocxXmlReader::readStartElement()
{
    m_xmlReader.readNextStartElement();
    while (!m_xmlReader.isEndElement()) {
        if (m_xmlReader.tokenType() == QXmlStreamReader::StartDocument
                || m_xmlReader.name() == QStringLiteral("body")
                || m_xmlReader.name() == QStringLiteral("document")) {
            m_xmlReader.readNextStartElement();
            continue;
        }
        qDebug() << " out line name " << m_xmlReader.name();
        if (m_xmlReader.name() == QStringLiteral("tbl")){
            //DocxTable table = new DocxTable()
        } else {
            DocxParagraph *para = new DocxParagraph();
            addMarketAtributes(para);
//            if (m_xmlReader.isCharacters() && !m_xmlReader.isWhitespace()) {
//                para->addTextChild(m_xmlReader.text());
//            }
            readPMark(para);
            m_paragraphs.append(para);
        }
        m_xmlReader.readNextStartElement();
    }
}

void DocxXmlReader::readStartElement(DocxParagraph *parent)
{
    m_xmlReader.readNextStartElement();
    if (!m_xmlReader.isEndElement()) {
        TagElement *child = new TagElement(elementName());
        parent->addChild(child);
    }
}

void DocxXmlReader::readPMark(DocxParagraph *parent)
{
    qDebug() << "enter element  : " << m_xmlReader.name().toString();
    if (m_xmlReader.name().toString() != strParagraph)
        return;

    // p paragraph
    DocxParagraph *paragraph = new DocxParagraph();
    addMarketAtributes(paragraph);

    // style Property
    if (m_xmlReader.name() == QStringLiteral("pPr")) {
        TagElement *style = new TagElement(elementName());
        addMarketAtributes(style);
        // child
        if (readNextMark()) {
            readCommonMark(style);
        }
        paragraph->addStyleProperty(style);
    }
    readNextMark();
    // p content element
    while (m_xmlReader.tokenType() != QXmlStreamReader::EndElement
           && m_xmlReader.name().toString() != strParagraph)
    {
        readRunMark(paragraph);
        readNextMark();
    }

    parent->addChild(paragraph);
}

void DocxXmlReader::readRunMark(DocxParagraph *parent)
{
    QString strName = elementName();
    if (strName.isEmpty())
        return;
    TagElement *run = new TagElement(strName);
    addMarketAtributes(run);

    readNextMark();
    readCommonMark(run);

    parent->addChild(run);

    readNextMark();
    if (m_xmlReader.tokenType() == QXmlStreamReader::EndElement && m_xmlReader.name().toString() == strRun)
        return;
    else
        readRunMark(parent);
}

void DocxXmlReader::readCommonMark(TagElement *parent)
{
    qDebug() << "element token  " << m_xmlReader.tokenString() << " name " << m_xmlReader.name();
//    if (!m_xmlReader.isStartElement() || !m_xmlReader.isCharacters())
//        return;

    if (m_xmlReader.isCharacters()) {
        readCharactersMark(parent);
        readNextMark();
        readCommonMark(parent);
        return;

    }
    TagElement *child = new TagElement(elementName());
    addMarketAtributes(child);

    parent->addChild(child);

    if (readNextMark())
        readCommonMark(child);
}

void DocxXmlReader::readCharactersMark(TagElement *parent)
{
    TagElement *chara =  new TagElement(elementName());
    addMarketAtributes(chara);
    chara->setCharaters(m_xmlReader.text().toString());
    parent->addChild(chara);
}

/*!
 * \brief add property
 * \param para
 */
void DocxXmlReader::addMarketAtributes(DocxParagraph *para)
{
    for (const QXmlStreamAttribute &att : m_xmlReader.attributes()) {
        QString attName = att.prefix().isEmpty() ? att.name().toString() : att.prefix().toString() + strcolon + att.name().toString();
        para->addProperty(attName, att.value().toString());
    }
}

/*!
 * \brief add property
 * \param para
 */
void DocxXmlReader::addMarketAtributes(TagElement *element)
{
    for (const QXmlStreamAttribute &att : m_xmlReader.attributes()) {
        QString attName = att.prefix().isEmpty() ? att.name().toString() : att.prefix().toString() + strcolon + att.name().toString();
        element->addProperty(attName, att.value().toString());
    }
}

bool DocxXmlReader::readNextMark()
{
    m_xmlReader.readNext();
    checkSkipMark();
    qDebug() << " readNext Mark Type" << m_xmlReader.tokenString() << m_xmlReader.name();
    if ( m_xmlReader.tokenType() == QXmlStreamReader::StartElement)
        return true;
    return false;
}

/*!
 * \brief skip invalid element as comment or DTD
 */
void DocxXmlReader::checkSkipMark()
{
    qDebug() << " check Skip Mark  " << m_xmlReader.tokenString() << m_xmlReader.name();
    if (m_xmlReader.tokenType() == QXmlStreamReader::Comment || m_xmlReader.tokenType() == QXmlStreamReader::DTD || m_xmlReader.name().isEmpty()) {
        m_xmlReader.readNext();
        checkSkipMark();
    }
}

QString DocxXmlReader::elementName() const
{
    QString strName = m_xmlReader.prefix().toString().isEmpty() ? m_xmlReader.name().toString()
                                                     : m_xmlReader.prefix().toString() + strcolon + m_xmlReader.name().toString();

    qDebug() << " element Name : " << strName
             << "  other property" << m_xmlReader.dtdName().toString()
             << " -- " << m_xmlReader.namespaceUri().toString();
    return strName;
}

QByteArray DocxXmlReader::saveToXmlData()
{
    QByteArray data;
    QBuffer buffer(&data);
    buffer.open(QIODevice::WriteOnly);
    QXmlStreamWriter writer(&buffer);
    saveElement(&writer);
    return data;
}

void DocxXmlReader::saveElement(QXmlStreamWriter *writer)
{
    for (const DocxParagraph *ele: m_paragraphs)
        ele->saveToXmlElement(writer);
}

}
