#ifndef ABSFOOTANDHEADER_H
#define ABSFOOTANDHEADER_H
#include "abstractooxmlfile.h"
#include "docx_global.h"
#include "itagelement.h"
#include "docxfont.h"
#include "docxparagraph.h"

namespace TDocx
{
enum class HeaderFooterType
{
    HeaderPrimary,
    FooterPrimary,
};

class DOCX_EXPORT FootAndHeader : public AbstractOOXmlFile
{
public:
    FootAndHeader(const HeaderFooterType &flag);
    void addProperty(QString name, QString value);
    void addChild(ISaveToXml *child);
    void remoevChild(ISaveToXml *child);
    QString startElement() const;
    void saveToXmlFile(QIODevice *device) const;
    bool loadFromXmlFile(QIODevice *device);
    void write(const QString &text, const RunAlignment &alignment = RunAlignment::Left);
    void showNumber();

    virtual ~FootAndHeader();

    DocxFont font() const;
    void setFont(const DocxFont &font);

    void checkAlignment(const RunAlignment &alignment);
    QString name() const;
    void setName(const QString &name);

    QString id() const;
    void setId(const QString &id);

    QString type() const;
    void setType(const QString &type);

    QString reference() const;
    void setReference(const QString &reference);

    HeaderFooterType flag() const;
    void setFlag(const HeaderFooterType &flag);

    QString prefix() const;
    void setPrefix(const QString &prefix);

private:
    FootAndHeader(const CreateFlag &flag);
    QString typeByHeaderFooterType(const HeaderFooterType &flag) const;
    QString referenceByHeaderFooterType(const HeaderFooterType &flag) const;
    QString prefixByHeaderFooterType(const HeaderFooterType &flag) const;

private:
    QString m_prefix;
    QString m_reference;
    QString m_type;
    RunAlignment m_alignment = RunAlignment::None;
    HeaderFooterType m_flag;
    DocxParagraph m_Paragraph;
    QString m_name;
    QString m_id;
};

//class DOCX_EXPORT DocxFooter : public FootAndHeader
//{
//public:
//    DocxFooter();
//    QString startElement() const;
//};

//class DOCX_EXPORT DocxHeader : public FootAndHeader
//{
//public:
//    DocxHeader();
//    QString startElement() const;
//};

}

#endif // ABSFOOTANDHEADER_H
