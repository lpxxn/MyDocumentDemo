#include "absfootandheader.h"

#include <QXmlStreamWriter>

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


AbsFootAndHeader::AbsFootAndHeader(const CreateFlag &flag)
    : AbstractOOXmlFile(flag)
{
}

void AbsFootAndHeader::saveToXmlElement(QXmlStreamWriter *writer) const
{
    writer->writeStartElement(startElement());
    writer->writeNamespace(wpc, QStringLiteral("wpc"));
    writer->writeNamespace(mc, QStringLiteral("mc"));
    writer->writeNamespace(o, QStringLiteral("o"));
    writer->writeNamespace(r, QStringLiteral("r"));
    writer->writeNamespace(m, QStringLiteral("m"));
    writer->writeNamespace(v, QStringLiteral("v"));
    writer->writeNamespace(wp14, QStringLiteral("wp14"));
    writer->writeNamespace(wp, QStringLiteral("wp"));
    writer->writeNamespace(w10, QStringLiteral("w10"));
    writer->writeNamespace(w, QStringLiteral("w"));
    writer->writeNamespace(w14, QStringLiteral("w14"));
    writer->writeNamespace(wpg, QStringLiteral("wpg"));
    writer->writeNamespace(wpi, QStringLiteral("wpi"));
    writer->writeNamespace(wne, QStringLiteral("wne"));
    writer->writeNamespace(wps, QStringLiteral("wps"));
    writer->writeAttribute(QStringLiteral("mc:Ignorable"), QStringLiteral("w14 wp14"));

    for (const pairValue &att : m_properties) {
        writer->writeAttribute(att.first, att.second);
    }

    for (const ISaveToXml *ele : m_childs) {
        ele->saveToXmlElement(writer);
    }

    writer->writeEndElement();
}

void AbsFootAndHeader::addProperty(QString name, QString value)
{
    m_properties.append(pairValue(name, value));
}

void AbsFootAndHeader::addChild(TDocx::ISaveToXml *child)
{
    m_childs.append(child);
}

void AbsFootAndHeader::remoevChild(TDocx::ISaveToXml *child)
{
    if (m_childs.contains(child)) {
        m_childs.removeOne(child);
        delete child;
        child = nullptr;
    }
}

AbsFootAndHeader::~AbsFootAndHeader()
{
    qDeleteAll(m_childs);
}

void AbsFootAndHeader::saveToXmlFile(QIODevice *device) const
{
    QXmlStreamWriter writer(device);
    saveToXmlElement(&writer);
}

bool AbsFootAndHeader::loadFromXmlFile(QIODevice *device)
{
    return true;
}
// end AbsFootAndHeader


// begin DocxFooter
DocxFooter::DocxFooter()
    : AbsFootAndHeader(CreateFlag::F_NewFromScratch)
{

}

QString DocxFooter::startElement() const
{
    return QStringLiteral("w:ftr");
}
// end DocxFooter

// begin DocxHeader
DocxHeader::DocxHeader()
    : AbsFootAndHeader(CreateFlag::F_NewFromScratch)
{

}

QString DocxHeader::startElement() const
{
    return QStringLiteral("w:hdr");
}
// end DocxHeader



}








