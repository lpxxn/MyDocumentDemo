#ifndef ITAGELEMENT_H
#define ITAGELEMENT_H
#include "docx_global.h"

#include <QString>
#include <QPair>
#include <QVector>
#include <QList>
#include <QXmlStreamWriter>
namespace TDocx
{
class ITagElement;

template<class T>
class DOCX_EXPORT ITagIterator
{
public:
    virtual bool hasNext() const = 0;
    virtual T* next() const = 0;
};

class DOCX_EXPORT TagElementIterator : public ITagIterator<ITagElement>
{
public:
    TagElementIterator(const ITagElement *element);
    bool hasNext() const;
    ITagElement *next() const;
private:
    const ITagElement *m_tagElement;
    mutable int m_currentIndex;
};


class DOCX_EXPORT ITagElement
{
public:
    ITagElement(QString name);
    virtual void addProperty(QString name, QString value);
    QString name() const { return m_tagName; }

    virtual ~ITagElement();

    virtual void addChild(ITagElement *child);
    virtual void remoevChild(ITagElement *child);
    virtual void saveToXmlElement(QXmlStreamWriter *writer) const;
    TagElementIterator createIterator() const;

private:
    QString m_tagName;
    typedef QPair<QString, QString> pairValue;
    QVector<pairValue> m_properties;
    QList<ITagElement*> m_childs;
    friend class TagElementIterator;

};
}
#endif // ITAGELEMENT_H
