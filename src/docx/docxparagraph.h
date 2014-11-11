#ifndef DOCXPARAGRAPH_H
#define DOCXPARAGRAPH_H
#include "docx_global.h"
#include "itagelement.h"
#include "docxfont.h"
#include "docxparagraphproperty.h"

namespace TDocx
{
//class DocxParagraph;
//class ParagraphTagIterator : public ITagIterator<ISaveToXml>
//{
//public:
//    ParagraphTagIterator(const DocxParagraph *element);
//    bool hasNext() const;
//    ISaveToXml *next() const;
//private:
//    const DocxParagraph *m_tagElement;
//    mutable int m_currentIndex;
//};

class DocxParagraph : public ITagElement
{
public:
    DocxParagraph();

    void saveToXmlElement(QXmlStreamWriter *writer) const;

    virtual ~DocxParagraph();

    QString text() const;
    void setText(const QString &text);
    DocxFont& font();
    void setFont(const DocxFont &font);
    void addStyleProperty(TagElement *element);

private:
    void addProperty(QString name, QString value);
    void addChild(ISaveToXml *child);
    void remoevChild(ISaveToXml *child);

private:
    typedef QPair<QString, QString> pairValue;
    QVector<pairValue> m_properties;
    QString m_text;
    DocxFont m_font;    
    DocxParagraphProperty m_property;
    //friend class StyleTagIterator;

};
}

#endif // DOCXPARAGRAPH_H
