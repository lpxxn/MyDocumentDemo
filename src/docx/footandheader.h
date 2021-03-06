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
class AbstractDocument;
class DOCX_EXPORT FootAndHeader : public AbstractOOXmlFile
{
public:
    FootAndHeader(const AbstractDocument *doc, const HeaderFooterType &flag = HeaderFooterType::HeaderPrimary);
    void addProperty(QString name, QString value);
    void addChild(ISaveToXml *child);
    void remoevChild(ISaveToXml *child);
    QString startElement() const;
    void saveToXmlFile(QIODevice *device) const;
    bool loadFromXmlFile(QIODevice *device);
    void setAlignment(const RunAlignment &alignment = RunAlignment::Left);
    void write(const QString &text, const RunAlignment &alignment);
    void insertImg(const QString &imgName, const QSize &size);
    void showNumber();

    virtual ~FootAndHeader();        

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

    void write(const QString &text);
private:
    FootAndHeader(const CreateFlag &flag);
    QString typeByHeaderFooterType(const HeaderFooterType &flag) const;
    QString referenceByHeaderFooterType(const HeaderFooterType &flag) const;
    QString prefixByHeaderFooterType(const HeaderFooterType &flag) const;

private:
    bool m_haveImg = false;
    const AbstractDocument *m_doc;
    QString m_prefix;
    QString m_reference;
    QString m_type;
    RunAlignment m_alignment = RunAlignment::None;
    HeaderFooterType m_flag;
    DocxParagraph m_Paragraph;
    QString m_name;
    QString m_id;
};

}

#endif // ABSFOOTANDHEADER_H
