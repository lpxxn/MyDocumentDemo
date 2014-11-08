#ifndef DOCXSTYLEHEADING_H
#define DOCXSTYLEHEADING_H
#include "itagelement.h"

namespace TDocx
{
class AbsHeading : public ITagElement
{
public:
    AbsHeading();

    void saveToXmlElement(QXmlStreamWriter *writer) const;
    void addProperty(QString name, QString value);
    void addChild(ITagElement *child);
    void remoevChild(ITagElement *child);

    virtual ITagElement* pPrElement() = 0;
    virtual ITagElement* rPrElement() = 0;

private:
    typedef QPair<QString, QString> pairValue;
    QVector<pairValue> m_properties;
    QList<ITagElement*> m_childs;
};

//class Heading1 : public AbsHeading
//{

//};

}

#endif // DOCXSTYLEHEADING_H
