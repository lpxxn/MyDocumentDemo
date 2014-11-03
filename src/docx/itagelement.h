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

class DOCX_EXPORT ITagIterator
{
public:
    virtual bool hasNext() const = 0;
    virtual ITagElement* next() const = 0;
};

class DOCX_EXPORT ITagElement : public ITagIterator
{
public:
    ITagElement(QString name);
    virtual void addProperty(QString name, QString value);
    QString name() const { return m_tagName; }

    virtual ~ITagElement(){}

    virtual void addChild(ITagElement *child);
    virtual void remoevChild(ITagElement *child);
    virtual bool hasNext() const;
    virtual ITagElement *next() const;
    virtual void saveToXmlElement(QXmlStreamWriter *writer) const;

private:
    QString m_tagName;
    typedef QPair<QString, QString> pairValue;
    QVector<pairValue> m_properties;
    QList<ITagElement*> m_childs;
    mutable int m_currentIndex = 0;


};
}
#endif // ITAGELEMENT_H
