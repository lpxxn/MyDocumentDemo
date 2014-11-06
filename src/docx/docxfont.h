#ifndef DOCXFONT_H
#define DOCXFONT_H
#include "docx_global.h"
#include <QString>
#include <QColor>

class QXmlStreamWriter;
namespace TDocx
{
enum class DocxUnderline
{
    None,
    Single,
    Double
};

class DOCX_EXPORT DocxFont
{
public:
    DocxFont();
    DocxFont(const QString & family);

    virtual ~DocxFont();

    QString family() const { return m_family; }
    void setFamily(const QString &family) { m_family = family;}
    bool bold() const;
    void setBold(bool bold);
    bool italic() const;
    void setItalic(bool italic);

    QColor color() const;
    void setColor(const QColor &color);

    int size() const;
    void setSize(int size);

    double space() const;
    void setSpace(double space);

    DocxUnderline underline() const;
    void setUnderline(const DocxUnderline &underline);

    void saveToXmlElement(QXmlStreamWriter *writer) const;
private:
    QString enumToString(DocxUnderline under) const;

private:
    QString m_family;
    bool m_bold = false;
    bool m_italic = false;
    int m_size = 12;
    double m_spacing = 0;
    QString m_color;
    DocxUnderline m_underline =  DocxUnderline::None;


};
}

#endif // DOCXFONT_H
