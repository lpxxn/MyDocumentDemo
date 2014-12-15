#include "docxxmlreader.h"
#include "docxtable.h"
#include "itagelement.h"
#include "comdatafun.h"
#include "docxparagraph.h"

#include <QBuffer>
#include <QRegExp>
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
    m_table = new MergeTable(QStringLiteral("mytable"));
    m_table->addColumn({"name", "id", "age"});
    m_table->addRow({"zhangsan", "1", "20"});
    m_table->addRow({"lisi", "2", "30"});
    m_table->addRow({"wangwu", "3", "40"});
    m_singleEles.insert("name", "usa");
    m_singleEles.insert("liM", "testtesttesttesttest");
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
            m_paragraphs.append(ele);
            readMark(ele, m_xmlReader.name().toString());
            //readCommonMark(ele);


        } else if (m_xmlReader.name().toString() == strParagraph) {
            DocxParagraph *para = new DocxParagraph();
            para->setIsRead(true);
            m_paragraphs.append(para);
            addMarketAtributes(para);
            //readMark(para, strParagraph);
            readPeleMark(para, strParagraph);
        } else {
            TagElement *ele = new TagElement(elementName());
            addMarketAtributes(ele);
            m_paragraphs.append(ele);
            readMark(ele, m_xmlReader.name().toString());
            //readCommonMark(ele);
            //m_xmlReader.readNextStartElement();

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
            readCommonMark(parent, parent);
        readNextMark();
    }
}

void DocxXmlReader::readPeleMark(DocxParagraph *parent, const QString &markName)
{
    qDebug() << "enter element  : " << m_xmlReader.name().toString();
    if (m_xmlReader.name().toString() != markName)
        return;

    readNextMark();

    while (m_xmlReader.tokenType() != QXmlStreamReader::EndElement
           && m_xmlReader.name().toString() != markName)
    {
        // property
        if (m_xmlReader.name() == strpPr) {
            TagElement *eleStyle = new TagElement(elementName());
            addMarketAtributes(eleStyle);

            readMark(eleStyle, strpPr);
            //readCommonMark(eleStyle);
            parent->addStyleProperty(eleStyle);
            readNextMark();
        }

        if (m_xmlReader.name() == strfldSimple)
            readfldSimpleMark(parent);
        else
            readCommonMark(parent, parent);
        readNextMark();
    }
}

void DocxXmlReader::readCommonMark(ITagElement *parent, ITagElement *preParent)
{
    qDebug() << "element token  " << m_xmlReader.tokenString() << " name " << m_xmlReader.name();

    QString markName = m_xmlReader.name().toString();
    if (markName.isEmpty() || m_xmlReader.tokenType() ==  QXmlStreamReader::EndElement)
        return;
    if (m_xmlReader.name() == strfldSimple)
        readfldSimpleMark(parent, preParent);
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

        while (m_xmlReader.tokenType() == QXmlStreamReader::StartElement
               || m_xmlReader.tokenType() == QXmlStreamReader::Characters) {
            readCommonMark(child, preParent);
            readNextMark();
        }

        if (isEndElement(markName)) {
            return;
        }
    }
    readCommonMark(parent, preParent);
}
// replace element method


void DocxXmlReader::readfldSimpleMark(ITagElement *parent, ITagElement *preParent)
{
    if (preParent != nullptr)
        qDebug() << " parent name " << preParent->name();
    QString contentStr = m_xmlReader.readElementText(QXmlStreamReader::IncludeChildElements);
    // capture string
    QRegExp reg(QStringLiteral("[a-zA-Z]+\:*[a-zA-Z]*"));
    int pos = reg.indexIn(contentStr);
    if (pos < 0)
        return;

    contentStr = reg.cap();
    // table
    if(contentStr.contains(':')) {
        // start table
        QStringList strList = contentStr.split(':');
        if (strList.count() >= 2)
            if (strList.at(0).toUpper() == startMarkStr.toUpper()) {
                m_tableMergeInfo = TableMergeInfo(this, preParent);
                m_tableMergeInfo.setTableName(strList.at(1));
            } else if (strList.at(0).toUpper() == endMarkStr.toUpper()) {
                m_tableMergeInfo.setEndTableMark();
            }
        return;
    }
    if (m_tableMergeInfo.isValid()) {
        m_tableMergeInfo.appendMarks(contentStr, parent);
        return;
    }

    // end table

    // signal

    TagElement *rele = new TagElement(QStringLiteral("w:r"));
    TagElement *wele = new TagElement(QStringLiteral("w:t"));

    rele->addChild(wele);

    for (const QString &key : m_singleEles.keys()) {
        if (key.toUpper() == contentStr.toUpper()) {
            wele->setCharaters(m_singleEles.value(key));
            break;
        }
    }



    //    for (;m_xmlReader.readNext();) {
    //        if (m_xmlReader.name().toString() == strText) {
    //            qDebug() << m_xmlReader.text() << "  name  " << m_xmlReader.name().toString();
    //            QString contentStr = m_xmlReader.readElementText().trimmed();
    //            qDebug() << contentStr;
    //            contentStr += QStringLiteral("new NEW NEW");
    //            wele->setCharaters(contentStr);

    //            parent->addChild(rele);
    //        }

    //        if (isEndElement(strfldSimple)) {
    //            break;
    //        }
    //    }


    if (!wele->haveCharaters()) {
        delete rele;
        rele = nullptr;
    } else {
        parent->addChild(rele);
    }
}

// end replace element method

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
 * \brief add property
 * \param para
 */
void DocxXmlReader::addMarketAtributes(DocxParagraph *para)
{
    for (const QXmlStreamAttribute &att : m_xmlReader.attributes()) {
        if (att.name().toString() ==  QStringLiteral("rsidR"))
            continue;
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

//********************************
// begin TableMergeInfo
//********************************

TableMergeInfo::TableMergeInfo()
{

}

TableMergeInfo::TableMergeInfo(DocxXmlReader *xmlReader, ITagElement *parent)
    : TableMergeInfo()
{
    m_parent = parent;
    m_xmlReader = xmlReader;
}

void TableMergeInfo::setParent(TagElement *parent)
{

}

QString TableMergeInfo::tableName() const
{
    return m_tableName;
}

void TableMergeInfo::setTableName(const QString &name)
{
    m_tableName = name;
}

TagElement * TableMergeInfo::mergeParagraphElement(QString str, int rowIndex, QList<QString> cols)
{
    TagElement *pele = new TagElement("w:p");

    pele->addChild(mergeRunElement(str, rowIndex, cols));

    return pele;
}

TagElement *TableMergeInfo::mergeRunElement(QString str, int rowIndex, QList<QString> cols)
{
    TagElement *rele = new TagElement("w:r");
    TagElement *tele = new TagElement("w:t");
    rele->addChild(tele);

    int colIndex = cols.indexOf(str.toUpper());
    if (colIndex > -1) {
        QString str = m_xmlReader->m_table->value(colIndex, rowIndex);
        tele->setCharaters(str);
    } else {
        tele->setCharaters("aaa");
    }
    return rele;
}

TagElement * TableMergeInfo::mergeTableElement(int rowIndex, QList<QString> cols)
{
    TagElement *rowEle = new TagElement("w:tr");
    for (const QString &str : m_marks) {
        TagElement *cEle = new TagElement("w:tc");
        cEle->addChild(mergeParagraphElement(str, rowIndex, cols));

        rowEle->addChild(cEle);
    }
    return rowEle;
}


void TableMergeInfo::setEndTableMark()
{
    if (!isValid())
        return;
    QList<QString> cols = m_xmlReader->m_table->cols();
    if (m_parent != nullptr && m_parent->name().contains("tbl", Qt::CaseInsensitive)) {
        for (int rowIndex = 1; rowIndex < m_xmlReader->m_table->rowCount(); rowIndex++) {
            TagElement *ele = mergeTableElement(rowIndex, cols);
            m_parent->addChild(ele);
        }
    } else {        
        DocxParagraph *paraP = static_cast<DocxParagraph*>(m_xmlReader->m_paragraphs.last());

        // body add child
        for (int rowIndex = 0; rowIndex < m_xmlReader->m_table->rowCount(); rowIndex++) {
            for (const QString &str : m_marks) {
                TagElement *ele = mergeParagraphElement(str, rowIndex, cols);
                if (paraP != nullptr) {
                    DocxParagraphProperty *pstyle = new DocxParagraphProperty(paraP->property());
                    ele->insertChild(pstyle);
                }
                m_xmlReader->m_paragraphs.append(ele);
            }
        }
    }
}

void TableMergeInfo::clearInfo()
{
    m_tableName.clear();
}

bool TableMergeInfo::isValid()
{
    return !m_tableName.isEmpty();
}

void TableMergeInfo::appendMarks(const QString markName, ITagElement *parent)
{
    m_marks.append(markName);
    QList<QString> cols = m_xmlReader->m_table->cols();
    parent->addChild(mergeRunElement(markName, 0, cols));

}

}
