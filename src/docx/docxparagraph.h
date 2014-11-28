#ifndef DOCXPARAGRAPH_H
#define DOCXPARAGRAPH_H
#include "docx_global.h"
#include "itagelement.h"
#include "docxfont.h"
#include "docxparagraphproperty.h"

namespace TDocx
{

enum class RunAlignment
{
    None = 0,
    Left,
    Center,
    Right
};

QString runAlignmentToString(const RunAlignment &format);

class DocxParagraph;
class ParagraphTagIterator : public ITagIterator<ISaveToXml>
{
public:
    ParagraphTagIterator(const DocxParagraph *element);
    bool hasNext() const;
    ISaveToXml *next() const;
private:
    const DocxParagraph *m_paragraph;
    mutable int m_currentIndex;
};

class DOCX_EXPORT DocxParagraph : public ITagElement
{
public:
    DocxParagraph();

    virtual void saveToXmlElement(QXmlStreamWriter *writer) const;

    virtual ~DocxParagraph();

    void addStyleProperty(TagElement *element);    
    ParagraphTagIterator createIterator() const;
    void setAlignment(const RunAlignment &format);
    void addProperty(QString name, QString value);
    void addChild(ISaveToXml *child);
    void remoevChild(ISaveToXml *child);    
    void addTextChild(const QString &text, const DocxFont &font = DocxFont());
    void addRunChild(ISaveToXml *child);

protected:
    typedef QPair<QString, QString> pairValue;
    QVector<pairValue> m_properties;        
    DocxParagraphProperty m_property;
    QList<ISaveToXml *> m_childs;    
    friend class ParagraphTagIterator;

};
}

#endif // DOCXPARAGRAPH_H
