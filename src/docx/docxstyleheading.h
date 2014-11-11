#ifndef DOCXSTYLEHEADING_H
#define DOCXSTYLEHEADING_H
#include "itagelement.h"

namespace TDocx
{
enum class HeadingLevel
{
    head1 = 1,
    head2,
    head3,
    head4,
    head5,
    head6,
    head7,
    head8,
    head9
};

class StyleTagElement;
class  AbsHeading : public ITagElement
{
public:
    AbsHeading();
    void iniHeading();

    virtual ~AbsHeading(){}

    void saveToXmlElement(QXmlStreamWriter *writer) const;
    void addProperty(QString name, QString value);
    void addChild(ISaveToXml *child);
    void remoevChild(ISaveToXml *child);
    QString headId() const;

    virtual ITagElement* pPrElement() = 0;
    virtual ITagElement* rPrElement() = 0;
    virtual HeadingLevel headLevel() const = 0;

private:
    typedef QPair<QString, QString> pairValue;
    QVector<pairValue> m_properties;
    QList<ISaveToXml *> m_childs;
    StyleTagElement *m_head;
};

class Heading1 : public AbsHeading
{
public:
    Heading1();
    ITagElement *pPrElement();
    ITagElement *rPrElement();    
    HeadingLevel headLevel() const;
};

class Heading2 : public AbsHeading
{
public:
    Heading2();

    ITagElement *pPrElement();
    ITagElement *rPrElement();
    HeadingLevel headLevel() const;
};

class Heading3 : public AbsHeading
{
public:
    Heading3();

    ITagElement *pPrElement();
    ITagElement *rPrElement();
    HeadingLevel headLevel() const;
};

class Heading4 : public AbsHeading
{
public:
    Heading4();

    ITagElement *pPrElement();
    ITagElement *rPrElement();
    HeadingLevel headLevel() const;
};

class Heading5 : public AbsHeading
{
public:
    Heading5();
    ITagElement *pPrElement();
    ITagElement *rPrElement();
    HeadingLevel headLevel() const;
};

class Heading6 : public AbsHeading
{
public:
    Heading6();
    ITagElement *pPrElement();
    ITagElement *rPrElement();
    HeadingLevel headLevel() const;
};

class Heading7 : public AbsHeading
{
public:
    Heading7();
    ITagElement *pPrElement();
    ITagElement *rPrElement();
    HeadingLevel headLevel() const;
};

class Heading8 : public AbsHeading
{
public:
    Heading8();
    ITagElement *pPrElement();
    ITagElement *rPrElement();
    HeadingLevel headLevel() const;
};

class Heading9 : public AbsHeading
{
public:
    Heading9();
    ITagElement *pPrElement();
    ITagElement *rPrElement();
    HeadingLevel headLevel() const;
};


class HeadingFactory
{
public:
    HeadingFactory();
    static AbsHeading* heading(HeadingLevel headLevel);
};
}

#endif // DOCXSTYLEHEADING_H
