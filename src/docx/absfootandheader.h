#ifndef ABSFOOTANDHEADER_H
#define ABSFOOTANDHEADER_H
#include "abstractooxmlfile.h"
#include "docx_global.h"
#include "itagelement.h"

namespace TDocx
{
class AbsFootAndHeader : public ITagElement ,public AbstractOOXmlFile
{
public:
    AbsFootAndHeader(const CreateFlag &flag);
    void saveToXmlElement(QXmlStreamWriter *writer) const;
    void addProperty(QString name, QString value);
    void addChild(ISaveToXml *child);
    void remoevChild(ISaveToXml *child);
    virtual QString startElement() const = 0 ;

    virtual ~AbsFootAndHeader();

    // AbstractOOXmlFile interface
public:
    void saveToXmlFile(QIODevice *device) const;
    bool loadFromXmlFile(QIODevice *device);

private:
    typedef QPair<QString, QString> pairValue;
    QVector<pairValue> m_properties;
    QList<ISaveToXml *> m_childs;

};

class DocxFooter : public AbsFootAndHeader
{
public:
    DocxFooter();
    QString startElement() const;
};

class DocxHeader : public AbsFootAndHeader
{
public:
    DocxHeader();
    QString startElement() const;
};

}

#endif // ABSFOOTANDHEADER_H
