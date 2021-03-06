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
class TagElement;

template<class T>
class ITagIterator
{
public:
    virtual bool hasNext() const = 0;
    virtual T* next() const = 0;
};

class ISaveToXml
{
public:
    virtual void saveToXmlElement(QXmlStreamWriter *writer) const = 0;
};

class ITagElement : public ISaveToXml
{
public:
    virtual void addProperty(QString tagName, QString value) = 0;
    virtual ~ITagElement() {}
    virtual QString tagName() const = 0;
    virtual void addChild(ISaveToXml *child) = 0;
    virtual void removeChild(ISaveToXml *child) = 0;
    virtual void saveToXmlElement(QXmlStreamWriter *writer) const = 0;
};

class TagElementIterator : public ITagIterator<ISaveToXml>
{
public:    
    TagElementIterator(const TagElement *element);
    bool hasNext() const;
    ISaveToXml *next() const;
private:
    const TagElement *m_tagElement;
    mutable int m_currentIndex;
};

//
class TagElement : public ITagElement
{
public:
    TagElement(const QString &tagName);
    void addProperty(QString tagName, QString value);
    QString tagName() const { return m_tagName; }
    void setCharaters(const QString &test);

    virtual ~TagElement();

    void addChild(ISaveToXml *child);
    void insertChild(ISaveToXml *child ,int index = 0);
    ITagElement* parent();
    void removeChild(ISaveToXml *child);
    virtual void saveToXmlElement(QXmlStreamWriter *writer) const;
    TagElementIterator createIterator() const;
    bool haveCharaters() const;

private:
    QString m_tagName;
    QString m_charaters;
    typedef QPair<QString, QString> pairValue;
    QVector<pairValue> m_properties;
    QList<ISaveToXml *> m_childs;    
    friend class TagElementIterator;

};
}
#endif // ITAGELEMENT_H
