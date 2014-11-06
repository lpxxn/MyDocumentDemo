#include "docxfont.h"
#include <QXmlStreamWriter>

namespace TDocx
{
DocxFont::DocxFont()
{
}

DocxFont::DocxFont(const QString &family)
{
    m_family = family;
}

DocxFont::~DocxFont()
{

}
bool DocxFont::italic() const
{
    return m_italic;
}

void DocxFont::setItalic(bool italic)
{
    m_italic = italic;
}

QColor DocxFont::color() const
{
    return QColor(m_color);
}

void DocxFont::setColor(const QColor &color)
{
    m_color = color.name();
}

int DocxFont::size() const
{
    return m_size / 2;
}

/*!
 * \brief size 要乘以2才是word里的字体
 *
 * \param size
 */
void DocxFont::setSize(int size)
{
    m_size = size * 2;
}

double DocxFont::space() const
{
    return m_spacing / 20;
}

/*!
 * \brief space 要乘以20才是word里的space
 * \param space
 */
void DocxFont::setSpace(double space)
{
    m_spacing = space * 20;
}
DocxUnderline DocxFont::underline() const
{
    return m_underline;
}

void DocxFont::setUnderline(const DocxUnderline &underline)
{
    m_underline = underline;
}

void DocxFont::saveToXmlElement(QXmlStreamWriter *writer) const
{
    if(m_family.isEmpty())
        return;
    writer->writeStartElement(QStringLiteral("w:rFonts"));
    writer->writeAttribute(QStringLiteral("w:ascii"), QString::fromUtf8(m_family.toUtf8()));
    writer->writeAttribute(QStringLiteral("w:eastAsia"), QString::fromUtf8(m_family.toUtf8()));
    writer->writeAttribute(QStringLiteral("w:hAnsi"), QString::fromUtf8(m_family.toUtf8()));
    writer->writeAttribute(QStringLiteral("w:cs"), QString::fromUtf8(m_family.toUtf8()));
    writer->writeEndElement(); // end w:rFonts
    if (italic()) writer->writeEmptyElement(QStringLiteral("w:i"));
    if (bold()) writer->writeEmptyElement(QStringLiteral("w:b"));

    // color
    if (!m_color.isEmpty()) {
        writer->writeStartElement(QStringLiteral("w:color"));
        writer->writeAttribute(QStringLiteral("w:val"), m_color);
        writer->writeEndElement(); // end w:color
    }

    // spacing
    if (m_spacing != 0) {
        writer->writeStartElement(QStringLiteral("w:spacing"));
        writer->writeAttribute(QStringLiteral("w:val"), QString::number(m_spacing));
        writer->writeEndElement(); // end w:spacing
    }

    // size
    if (m_size != 12) {
        writer->writeStartElement(QStringLiteral("w:sz"));
        writer->writeAttribute(QStringLiteral("w:val"), QString::number(m_size));
        writer->writeEndElement(); // end w:sz
    }

    if (m_underline != DocxUnderline::None) {
        writer->writeStartElement(QStringLiteral("w:u"));
        writer->writeAttribute(QStringLiteral("w:val"), enumToString(m_underline));
        writer->writeEndElement(); // end w:u
    }



}

QString DocxFont::enumToString(DocxUnderline under) const
{
    switch (under) {
    case DocxUnderline::None: return QStringLiteral("none"); break;
    case DocxUnderline::Single: return QStringLiteral("single"); break;
    case DocxUnderline::Double: return QStringLiteral("double"); break;
    default: return QStringLiteral("none"); break;
    }
}

bool DocxFont::bold() const
{
    return m_bold;
}

void DocxFont::setBold(bool bold)
{
    m_bold = bold;
}


}
