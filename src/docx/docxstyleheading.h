#ifndef DOCXSTYLEHEADING_H
#define DOCXSTYLEHEADING_H
#include "itagelement.h"

namespace TDocx
{
enum class HeadingType
{
    header1 = 1,
    header2,
    header3,
    header4,
    header5,
    header6,
    header7,
    header8,
    header9
};


class  AbsHeading : public ITagElement
{
public:
    AbsHeading();
    void iniHeading();

    virtual ~AbsHeading(){}

    void saveToXmlElement(QXmlStreamWriter *writer) const;
    void addProperty(QString name, QString value);
    void addChild(ITagElement *child);
    void remoevChild(ITagElement *child);

    virtual ITagElement* pPrElement() = 0;
    virtual ITagElement* rPrElement() = 0;
    virtual HeadingType headLevel() = 0;

private:
    typedef QPair<QString, QString> pairValue;
    QVector<pairValue> m_properties;
    QList<ITagElement*> m_childs;
};

class Heading1 : public AbsHeading
{
public:
    Heading1();
    ITagElement *pPrElement();
    ITagElement *rPrElement();
    HeadingType headLevel();
};

class Heading2 : public AbsHeading
{
public:
    Heading2();

    ITagElement *pPrElement();
    ITagElement *rPrElement();
    HeadingType headLevel();
};

class Heading3 : public AbsHeading
{
public:
    Heading3();

    ITagElement *pPrElement();
    ITagElement *rPrElement();
    HeadingType headLevel();
};

class Heading4 : public AbsHeading
{
public:
    Heading4();

    ITagElement *pPrElement();
    ITagElement *rPrElement();
    HeadingType headLevel();
};

class Heading5 : public AbsHeading
{
public:
    Heading5();
    ITagElement *pPrElement();
    ITagElement *rPrElement();
    HeadingType headLevel();
};

class Heading6 : public AbsHeading
{
public:
    Heading6();
    ITagElement *pPrElement();
    ITagElement *rPrElement();
    HeadingType headLevel();
};

class Heading7 : public AbsHeading
{
public:
    Heading7();
    ITagElement *pPrElement();
    ITagElement *rPrElement();
    HeadingType headLevel();
};


}

#endif // DOCXSTYLEHEADING_H
