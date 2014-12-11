#ifndef DOCXPARAGRAPHPROPERTY_H
#define DOCXPARAGRAPHPROPERTY_H
#include "itagelement.h"

namespace TDocx
{
class DocxParagraphProperty;
class ParPropertyIterator : public ITagIterator<ISaveToXml>
{
public:
    ParPropertyIterator(const DocxParagraphProperty *paragraph);
    bool hasNext() const;
    ISaveToXml *next() const;

private:
    const DocxParagraphProperty *m_paragraph;
    mutable int m_currentIndex;
};

/*!
 * \brief paragraph property
 */
class DocxParagraphProperty : public ITagElement
{
public:
    DocxParagraphProperty();

    virtual ~DocxParagraphProperty();

    QString name() const;
    void addProperty(QString name, QString value);
    void addChild(ISaveToXml *child);
    void remoevChild(ISaveToXml *child);
    void saveToXmlElement(QXmlStreamWriter *writer) const;
    ParPropertyIterator createIterator() const;

private:
    typedef QPair<QString, QString> pairValue;
    QVector<pairValue> m_properties;
    QList<ISaveToXml*> m_childs;
    friend class ParPropertyIterator;
};
}


#endif // DOCXPARAGRAPHPROPERTY_H
