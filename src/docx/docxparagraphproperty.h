#ifndef DOCXPARAGRAPHPROPERTY_H
#define DOCXPARAGRAPHPROPERTY_H
#include "itagelement.h"

namespace TDocx
{
class DocxParagraphProperty;
class ParPropertyIterator : public ITagIterator<ITagElement>
{
public:
    ParPropertyIterator(const DocxParagraphProperty *paragraph);
    bool hasNext() const;
    ITagElement *next() const;

private:
    const DocxParagraphProperty *m_paragraph;
    mutable int m_currentIndex;
};

class DocxParagraphProperty : public ITagElement
{
public:
    DocxParagraphProperty();

public:
    void addProperty(QString name, QString value);
    void addChild(ITagElement *child);
    void remoevChild(ITagElement *child);
    void saveToXmlElement(QXmlStreamWriter *writer) const;
    ParPropertyIterator createIterator() const;

private:
    typedef QPair<QString, QString> pairValue;
    QVector<pairValue> m_properties;
    QList<ITagElement*> m_childs;
    friend class ParPropertyIterator;
};
}


#endif // DOCXPARAGRAPHPROPERTY_H
