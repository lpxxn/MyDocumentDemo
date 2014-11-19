#include "footandheader.h"

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


FootAndHeader::FootAndHeader(const CreateFlag &flag)
    : AbstractOOXmlFile(flag)
{
}

void FootAndHeader::addProperty(QString name, QString value)
{
    m_Paragraph.addProperty(name, value);
}

void FootAndHeader::addChild(TDocx::ISaveToXml *child)
{
    m_Paragraph.addChild(child);
}

void FootAndHeader::remoevChild(TDocx::ISaveToXml *child)
{
    m_Paragraph.remoevChild(child);
}

FootAndHeader::~FootAndHeader()
{

}
DocxFont FootAndHeader::font() const
{
    return m_Paragraph.font();
}

void FootAndHeader::setFont(const DocxFont &font)
{
    m_Paragraph.setFont(font);
}


void FootAndHeader::saveToXmlFile(QIODevice *device) const
{
    QXmlStreamWriter writer(device);
    writer.writeStartElement(startElement());
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
    writer.writeAttribute(QStringLiteral("mc:Ignorable"), QStringLiteral("w14 wp14"));

    m_Paragraph.saveToXmlElement(&writer);

    writer.writeEndElement();
}

bool FootAndHeader::loadFromXmlFile(QIODevice *device)
{
    return true;
}

void FootAndHeader::checkAlignment(const RunAlignment &alignment)
{
    if (alignment != m_alignment) {
        m_alignment = alignment;
        TagElement *ali = new TagElement(QStringLiteral("w:ptab"));
        ali->addProperty(QStringLiteral("w:relativeTo"), QStringLiteral("margin"));
        ali->addProperty(QStringLiteral("w:alignment"), runAlignmentToString(m_alignment));
        ali->addProperty(QStringLiteral("w:leader"), QStringLiteral("none"));
        m_Paragraph.addChild(ali);
    }
}
QString FootAndHeader::name() const
{
    return m_name;
}

void FootAndHeader::setName(const QString &name)
{
    m_name = name;
}
QString FootAndHeader::id() const
{
    return m_id;
}

void FootAndHeader::setId(const QString &id)
{
    m_id = id;
}



void FootAndHeader::write(const QString &text, const RunAlignment &alignment)
{
    if (!(int)alignment)
        checkAlignment(RunAlignment::Left);
    else
        checkAlignment(alignment);

    TagElement *ele = new TagElement(QStringLiteral("w:t"));
    ele->setCharaters(text);
    m_Paragraph.addChild(ele);
}
// end AbsFootAndHeader


// begin DocxFooter
DocxFooter::DocxFooter()
    : FootAndHeader(CreateFlag::F_NewFromScratch)
{

}

QString DocxFooter::startElement() const
{
    return QStringLiteral("w:ftr");
}
// end DocxFooter

// begin DocxHeader
DocxHeader::DocxHeader()
    : FootAndHeader(CreateFlag::F_NewFromScratch)
{

}

QString DocxHeader::startElement() const
{
    return QStringLiteral("w:hdr");
}
// end DocxHeader

}








