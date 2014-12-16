#include "existdocument.h"
#include "docxzipwriter.h"
#include "docxtable.h"
#include "docxdocument.h"

#include <QXmlStreamWriter>
#include <QFile>
#include <QBuffer>
#include <QDebug>


namespace TDocx
{
const QString wpc = QStringLiteral("http://schemas.microsoft.com/office/word/2010/wordprocessingCanvas");
const QString mc = QStringLiteral("http://schemas.openxmlformats.org/markup-compatibility/2006");
const QString o = QStringLiteral("urn:schemas-microsoft-com:office:office");
const QString r = QStringLiteral("http://schemas.openxmlformats.org/officeDocument/2006/relationships");
const QString m = QStringLiteral("http://schemas.openxmlformats.org/officeDocument/2006/math");
const QString v = QStringLiteral("urn:schemas-microsoft-com:vml");
const QString wp14 = QStringLiteral("http://schemas.microsoft.com/office/word/2010/wordprocessingDrawing");
const QString wp = QStringLiteral("http://schemas.openxmlformats.org/drawingml/2006/wordprocessingDrawing");
const QString w10 = QStringLiteral("urn:schemas-microsoft-com:office:word");
const QString w = QStringLiteral("http://schemas.openxmlformats.org/wordprocessingml/2006/main");
const QString w14 = QStringLiteral("http://schemas.microsoft.com/office/word/2010/wordml");
const QString wpg = QStringLiteral("http://schemas.microsoft.com/office/word/2010/wordprocessingGroup");
const QString wpi = QStringLiteral("http://schemas.microsoft.com/office/word/2010/wordprocessingInk");
const QString wne = QStringLiteral("http://schemas.microsoft.com/office/word/2006/wordml");
const QString wps = QStringLiteral("http://schemas.microsoft.com/office/word/2010/wordprocessingShape");


// exist Document

ExistDocument::ExistDocument(const QString &docxName)
    : AbstractOOXmlFile(CreateFlag::F_LoadFromExists)
{
    if (QFile::exists(docxName)) {
        QFile file(docxName);
        if (file.open(QFile::ReadOnly))
            loadFromXmlFile(&file);
    }
}

void ExistDocument::saveToXmlFile(QIODevice *device) const
{
    QXmlStreamWriter writer(device);
    writer.writeStartDocument(QStringLiteral("1.0"), true);
    writer.writeStartElement("w:document");
    writer.writeNamespace(wpc, QStringLiteral("wpc"));
    writer.writeNamespace(mc, QStringLiteral("mc"));
    writer.writeNamespace(o, QStringLiteral("o"));
    writer.writeNamespace(r, QStringLiteral("r"));
    writer.writeNamespace(m, QStringLiteral("m"));
    writer.writeNamespace(v, QStringLiteral("v"));
    writer.writeNamespace(wp14, QStringLiteral("wp14"));
    writer.writeNamespace(wp, QStringLiteral("wp"));
    writer.writeNamespace(w10, QStringLiteral("w10"));
    writer.writeNamespace(w, QStringLiteral("w"));
    writer.writeNamespace(w14, QStringLiteral("w14"));
    writer.writeNamespace(wpg, QStringLiteral("wpg"));
    writer.writeNamespace(wpi, QStringLiteral("wpi"));
    writer.writeNamespace(wne, QStringLiteral("wne"));
    writer.writeNamespace(wps, QStringLiteral("wps"));
    writer.writeAttribute(mc, QStringLiteral("Ignorable"), QStringLiteral("w14 wp14"));
    writer.writeStartElement(QStringLiteral("w:body"));
    writer.writeComment(QStringLiteral("body"));

    m_xmlReader->saveElement(&writer);

    writer.writeComment(QStringLiteral("end"));
    //device->write(strEndpr.toUtf8());
    //m_DocEndElement->saveToXmlElement(&writer);
//    if (!m_endElements.isEmpty()) {
//        TagElement *ele = m_endElements.back();
//        ele->saveToXmlElement(&writer);
//    } else {
//        TagElement *ele = initDocumentEndElement();
//        ele->saveToXmlElement(&writer);
//    }
    writer.writeEndElement();// end body

    writer.writeEndElement(); // end w:document
    writer.writeEndDocument();
}

bool ExistDocument::loadFromXmlFile(QIODevice *device)
{
    DocxZipReader zipReader(device);
    QStringList filePaths = zipReader.filePaths();

    //Load Content_Types file
    if (!filePaths.contains(QLatin1String("[Content_Types].xml")))
        return false;
    for (const QString &fpath : filePaths) {
        if (fpath == QString("word/document.xml")) {

            QByteArray data = zipReader.fileData(fpath);

            m_xmlReader = new DocxXmlReader(data);

        } else {
            QByteArray data = zipReader.fileData(fpath);
            m_otherFiles.insert(fpath, data);
        }
    }
//    m_contentTypes.loadFromXmlData(zipReader.fileData(QStringLiteral("[Content_Types].xml")));
//    QMapIterator<QString, QString> contentFile(m_contentTypes.contentFiles());
//    while (contentFile.hasNext()) {
//        contentFile.next();
//        QString strKey = contentFile.key();
//        strKey = strKey.remove(0, 1);
//        if (contentFile.key().contains(QString("document"))) {

//            QByteArray data = zipReader.fileData(strKey);

//            m_xmlReader = new DocxXmlReader(data);

//        } else {
//            QByteArray data = zipReader.fileData(strKey);
//            m_otherFiles.insert(strKey, data);
//        }
//    }
    return true;
}

bool ExistDocument::saveAs(const QString &name)
{
    QFile file(name);
    if (file.open(QIODevice::WriteOnly))
        return this->saveAs(&file);
    return false;
}

bool ExistDocument::saveAs(QIODevice *device)
{
    DocxZipWriter writer(device);

    QMapIterator<QString, QByteArray> iter(m_otherFiles);
    while (iter.hasNext()) {
        iter.next();
        writer.addFile(iter.key(), iter.value());
    }
    // word/document.xml
    writer.addFile(QStringLiteral("word/document.xml"), this->saveToXmlData());
    //this->saveToXmlFile(device);
    writer.close();
    return true;
}

void ExistDocument::writeln()
{

}

void ExistDocument::writeln(const QString &text, const RunAlignment alignment)
{

}

void ExistDocument::writeln(const QString &text, const DocxFont &font, const RunAlignment alignment)
{

}

void ExistDocument::writeHeading(const QString &text, const HeadingLevel headLevel, const DocxFont &font)
{

}

void ExistDocument::writeList(const DocxListFormat &listStyle, std::initializer_list<QString> outValus)
{

}

void ExistDocument::writeList(const DocxListFormat &listStyle, const QString &outStr, std::initializer_list<QString> inValus)
{

}

void ExistDocument::insertImage(const QString &imgName, const QSize &size)
{

}

void ExistDocument::insertTable(DocxTable *table)
{

}

void ExistDocument::insertSectionFooterAndHeader(std::initializer_list<FootAndHeader *> hfs, bool restarNum)
{

}

void ExistDocument::merge()
{
    m_xmlReader->readStartElement();
}

void ExistDocument::addSignalMergeElement(const QString &name, const QString &value)
{
    m_xmlReader->addSignalMergeElement(name, value);
}

void ExistDocument::addMergeTable(MergeTable *table)
{
//    m_table = new MergeTable(QStringLiteral("mytable"));
//    m_table->addColumn({"name", "id", "age"});
//    m_table->addRow({"zhangsan", "1", "20"});
//    m_table->addRow({"lisi", "2", "30"});
//    m_table->addRow({"wangwu", "3", "40"});
    m_xmlReader->addMergeTable(table);
}

}




