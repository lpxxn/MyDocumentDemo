#ifndef ABSFOOTANDHEADER_H
#define ABSFOOTANDHEADER_H
#include "abstractooxmlfile.h"
#include "docx_global.h"
#include "itagelement.h"
#include "docxfont.h"
#include "docxparagraph.h"

namespace TDocx
{
class DOCX_EXPORT FootAndHeader : public AbstractOOXmlFile
{
public:
    FootAndHeader(const CreateFlag &flag);
    void addProperty(QString name, QString value);
    void addChild(ISaveToXml *child);
    void remoevChild(ISaveToXml *child);
    virtual QString startElement() const = 0 ;
    void saveToXmlFile(QIODevice *device) const;
    bool loadFromXmlFile(QIODevice *device);
    void write(const QString &text, const RunAlignment &alignment = RunAlignment::Left);

    virtual ~FootAndHeader();

    DocxFont font() const;
    void setFont(const DocxFont &font);

    void checkAlignment(const RunAlignment &alignment);
    QString name() const;
    void setName(const QString &name);

    QString id() const;
    void setId(const QString &id);

private:
    RunAlignment m_alignment = RunAlignment::None;
    DocxParagraph m_Paragraph;
    QString m_name;
    QString m_id;
};

class DOCX_EXPORT DocxFooter : public FootAndHeader
{
public:
    DocxFooter();
    QString startElement() const;
};

class DOCX_EXPORT DocxHeader : public FootAndHeader
{
public:
    DocxHeader();
    QString startElement() const;
};

}

#endif // ABSFOOTANDHEADER_H
