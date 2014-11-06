#ifndef DOCXPARAGRAPH_H
#define DOCXPARAGRAPH_H
#include "docx_global.h"
#include "itagelement.h"
#include "docxfont.h"

namespace TDocx
{
class DocxParagraph;
class ParagraphTagIterator : public ITagIterator<ITagElement>
{
public:
    ParagraphTagIterator(const DocxParagraph *element);
    bool hasNext() const;
    ITagElement *next() const;
private:
    const DocxParagraph *m_tagElement;
    mutable int m_currentIndex;
};

class DocxParagraph : public ITagElement
{
public:
    DocxParagraph();
    void addProperty(QString name, QString value);
    void addChild(ITagElement *child);
    void remoevChild(ITagElement *child);
    void saveToXmlElement(QXmlStreamWriter *writer) const;

    virtual ~DocxParagraph();

    QString text() const;
    void setText(const QString &text);

    DocxFont& font();
    void setFont(const DocxFont &font);

private:
    typedef QPair<QString, QString> pairValue;
    QVector<pairValue> m_properties;
    QString m_text;
    DocxFont m_font;
    friend class StyleTagIterator;

};
}

#endif // DOCXPARAGRAPH_H
