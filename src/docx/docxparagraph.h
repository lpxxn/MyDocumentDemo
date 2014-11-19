#ifndef DOCXPARAGRAPH_H
#define DOCXPARAGRAPH_H
#include "docx_global.h"
#include "itagelement.h"
#include "docxfont.h"
#include "docxparagraphproperty.h"

namespace TDocx
{

enum class RunAligment
{
    None = 0,
    Left,
    Center,
    Right
};

QString RunAligmentToString(const RunAligment &format);

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

    void setText(const QString &text);
    DocxFont& font();
    void setFont(const DocxFont &font);
    void addStyleProperty(TagElement *element);
    void addContentElement(TagElement *element);    
    ParagraphTagIterator createIterator() const;
    void paragraphAligment(const RunAligment &format);
    void addProperty(QString name, QString value);
    void addChild(ISaveToXml *child);
    void remoevChild(ISaveToXml *child);    


protected:
    typedef QPair<QString, QString> pairValue;
    QVector<pairValue> m_properties;    
    DocxFont m_font;    
    DocxParagraphProperty m_property;
    QList<ISaveToXml *> m_childs;    
    friend class ParagraphTagIterator;

};
}

#endif // DOCXPARAGRAPH_H
