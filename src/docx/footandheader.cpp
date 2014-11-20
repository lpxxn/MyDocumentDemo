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

QString FootAndHeader::type() const
{
    return m_type;
}

void FootAndHeader::setType(const QString &type)
{
    m_type = type;
}


FootAndHeader::FootAndHeader(const HeaderFooterType &flag)
    : FootAndHeader(CreateFlag::F_NewFromScratch)
{
    m_flag = flag;
    setType(typeByHeaderFooterType(m_flag));
    setReference(referenceByHeaderFooterType(m_flag));
    setPrefix(prefixByHeaderFooterType(m_flag));
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

QString FootAndHeader::startElement() const
{
    switch (m_flag) {
    case HeaderFooterType::FooterPrimary: return QStringLiteral("w:ftr"); break;
    case HeaderFooterType::HeaderPrimary: return QStringLiteral("w:hdr"); break;
    }
}

QString FootAndHeader::typeByHeaderFooterType(const HeaderFooterType &flag) const
{
    switch (flag) {
    case HeaderFooterType::FooterPrimary:
    case HeaderFooterType::HeaderPrimary: return QStringLiteral("default"); break;
    }
}

QString FootAndHeader::referenceByHeaderFooterType(const HeaderFooterType &flag) const
{
    switch (flag) {
    case HeaderFooterType::FooterPrimary: return QStringLiteral("w:footerReference"); break;
    case HeaderFooterType::HeaderPrimary: return QStringLiteral("w:headerReference"); break;
    }
}

QString FootAndHeader::prefixByHeaderFooterType(const HeaderFooterType &flag) const
{
    switch (flag) {
    case HeaderFooterType::FooterPrimary: return QStringLiteral("footer"); break;
    case HeaderFooterType::HeaderPrimary: return QStringLiteral("header"); break;
    }
}
QString FootAndHeader::prefix() const
{
    return m_prefix;
}

void FootAndHeader::setPrefix(const QString &prefix)
{
    m_prefix = prefix;
}

HeaderFooterType FootAndHeader::flag() const
{
    return m_flag;
}

void FootAndHeader::setFlag(const HeaderFooterType &flag)
{
    m_flag = flag;
}

QString FootAndHeader::reference() const
{
    return m_reference;
}

void FootAndHeader::setReference(const QString &reference)
{
    m_reference = reference;
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

void FootAndHeader::showNumber()
{
    TagElement *ele = new TagElement(QStringLiteral("w:fldChar"));
    ele->addProperty(QStringLiteral("w:fldCharType"), QStringLiteral("begin"));
    m_Paragraph.addChild(ele);

    ele = new TagElement(QStringLiteral("w:instrText"));
    ele->setCharaters(QStringLiteral("PAGE"));
    m_Paragraph.addChild(ele);

    ele = new TagElement(QStringLiteral("w:fldChar"));
    ele->addProperty(QStringLiteral("w:fldCharType"), QStringLiteral("separate"));
    m_Paragraph.addChild(ele);

    ele = new TagElement(QStringLiteral("w:fldChar"));
    ele->addProperty(QStringLiteral("w:fldCharType"), QStringLiteral("end"));
    m_Paragraph.addChild(ele);

}
// end AbsFootAndHeader


// begin DocxFooter
//DocxFooter::DocxFooter()
//    : FootAndHeader(CreateFlag::F_NewFromScratch)
//{

//}

//QString DocxFooter::startElement() const
//{
//    return QStringLiteral("w:ftr");
//}
//// end DocxFooter

//// begin DocxHeader
//DocxHeader::DocxHeader()
//    : FootAndHeader(CreateFlag::F_NewFromScratch)
//{

//}

//QString DocxHeader::startElement() const
//{
//    return QStringLiteral("w:hdr");
//}
// end DocxHeader

}








