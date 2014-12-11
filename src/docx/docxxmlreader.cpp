#include "docxxmlreader.h"
#include "docxtable.h"
#include "itagelement.h"

#include <QBuffer>
#include <QDebug>

namespace TDocx
{
const QString strcolon = QStringLiteral(":");
const QString strParagraph = QStringLiteral("p");
const QString strpPr = QStringLiteral("pPr");
const QString strRun = QStringLiteral("r");
const QString strText = QStringLiteral("t");
const QString strfldSimple = QStringLiteral("fldSimple");

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
            TagElement *ele = new TagElement(elementName());
            addMarketAtributes(ele);
            readMark(ele, m_xmlReader.name().toString());
            //readCommonMark(ele);

            m_paragraphs.append(ele);            
        } else if (m_xmlReader.name().toString() == strParagraph) {
            DocxParagraph *para = new DocxParagraph();
            addMarketAtributes(para);            
            readMark(para, strParagraph);
            m_paragraphs.append(para);
        } else {
            TagElement *ele = new TagElement(elementName());
            addMarketAtributes(ele);
            readMark(ele, m_xmlReader.name().toString());
            //readCommonMark(ele);
            //m_xmlReader.readNextStartElement();
            m_paragraphs.append(ele);
        }
        qDebug() << " out line name " << m_xmlReader.name() << " type " << m_xmlReader.tokenString();
        if (m_xmlReader.tokenType() != QXmlStreamReader::StartElement)
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

//void DocxXmlReader::readPMark(DocxParagraph *parent)
//{
//    qDebug() << "enter element  : " << m_xmlReader.name().toString();
//    if (m_xmlReader.name().toString() != strParagraph)
//        return;

//    // p paragraph

//    readNextMark();
//    // style Property
//    if (m_xmlReader.name() == strpPr) {
//        TagElement *eleStyle = new TagElement(elementName());
//        addMarketAtributes(eleStyle);
//        readMark(eleStyle, strpPr);
//        //readCommonMark(eleStyle);
//        parent->addStyleProperty(eleStyle);
//        readNextMark();
//    }

//    // p content element
//    while (m_xmlReader.tokenType() != QXmlStreamReader::EndElement
//           && m_xmlReader.name().toString() != strParagraph)
//    {
//        readCommonMark(parent);
//        readNextMark();
//    }
//}

void DocxXmlReader::readMark(ITagElement *parent, const QString &markName)
{
    qDebug() << "enter element  : " << m_xmlReader.name().toString();
    if (m_xmlReader.name().toString() != markName)
        return;

    readNextMark();

    while (m_xmlReader.tokenType() != QXmlStreamReader::EndElement
           && m_xmlReader.name().toString() != markName)
    {
        if (m_xmlReader.name() == strfldSimple)
            readfldSimpleMark(parent);
        else
            readCommonMark(parent);
        readNextMark();
    }
}



//void DocxXmlReader::readRunMark(ITagElement *parent)
//{
//    QString strName = m_xmlReader.name().toString();
//    if (strName.isEmpty())
//        return;
//    TagElement *run = new TagElement(elementName());
//    addMarketAtributes(run);

//    if (strName == strText) {
//        QString contentStr = m_xmlReader.readElementText().trimmed();
//        run->setCharaters(contentStr);
//        while (m_xmlReader.tokenType() == QXmlStreamReader::EndElement) {
//            if (m_xmlReader.name().toString() == strRun) {
//                parent->addChild(run);
//                readNextMark();
//                return;
//            }
//            readNextMark();
//            if (m_xmlReader.tokenType() == QXmlStreamReader::StartElement || m_xmlReader.tokenType() == QXmlStreamReader::Characters)
//                break;
//        }
//    }

//    readNextMark();
//    readCommonMark(run);

//    parent->addChild(run);

//    readNextMark();
//    while (m_xmlReader.tokenType() == QXmlStreamReader::EndElement) {
//        if (m_xmlReader.name().toString() == strRun) {
//            readNextMark();
//            return;
//        }
//        readNextMark();
//        if (m_xmlReader.tokenType() == QXmlStreamReader::StartElement || m_xmlReader.tokenType() == QXmlStreamReader::Characters)
//            break;
//    }
//    readRunMark(run);
//}

void DocxXmlReader::readCommonMark(ITagElement *parent)
{
    qDebug() << "element token  " << m_xmlReader.tokenString() << " name " << m_xmlReader.name();

    QString markName = m_xmlReader.name().toString();
    if (markName.isEmpty() || m_xmlReader.tokenType() ==  QXmlStreamReader::EndElement)
        return;

    if (m_xmlReader.name() == strfldSimple)
        readfldSimpleMark(parent);
    else {

        TagElement *child = new TagElement(elementName());
        addMarketAtributes(child);
        parent->addChild(child);


        if (m_xmlReader.name().toString() == strText) {

            QString contentStr = m_xmlReader.readElementText().trimmed();
            child->setCharaters(contentStr);

            if (isEndElement(markName)) {
                return;
            }
        }

        readNextMark();
        if (isEndElement(markName))
            return;

        while (m_xmlReader.tokenType() == QXmlStreamReader::StartElement || m_xmlReader.tokenType() == QXmlStreamReader::Characters) {
            readCommonMark(child);
            readNextMark();
        }

        if (isEndElement(markName)) {
            return;
        }
    }
    readCommonMark(parent);
}

void DocxXmlReader::readfldSimpleMark(ITagElement *parent)
{
    TagElement *rele = new TagElement(QStringLiteral("w:r"));
    TagElement *wele = new TagElement(QStringLiteral("w:t"));
    rele->addChild(wele);

    for (;m_xmlReader.readNext();) {
        if (m_xmlReader.name().toString() == strText) {
            qDebug() << m_xmlReader.text();
            QString contentStr = m_xmlReader.readElementText().trimmed() + QStringLiteral("new NEW NEW");
            wele->setCharaters(contentStr);

            parent->addChild(rele);
        }

        if (isEndElement(strfldSimple)) {
            break;
        }
    }
    if (!wele->haveCharaters()) {
        delete rele;
        delete wele;
    }
}

bool DocxXmlReader::isEndElement(const QString &markName)
{
    while (m_xmlReader.tokenType() == QXmlStreamReader::EndElement) {
        if (m_xmlReader.name().toString() == markName) {
            return true;
        }
        readNextMark();
        if (m_xmlReader.tokenType() == QXmlStreamReader::StartElement || m_xmlReader.tokenType() == QXmlStreamReader::Characters)
            return false;
    }
    return false;
}


/*!
 * \brief text mark
 *
 * <w:t>
 * \param parent
 */
//void DocxXmlReader::readTMark(TagElement *parent)
//{

//}

//void DocxXmlReader::readCharactersMark(ITagElement *parent)
//{
//    TagElement *chara =  new TagElement(elementName());
//    addMarketAtributes(chara);
//    chara->setCharaters(m_xmlReader.text().toString());
//    parent->addChild(chara);
//}

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
    for (const ITagElement *ele: m_paragraphs)
        ele->saveToXmlElement(writer);
}


}
