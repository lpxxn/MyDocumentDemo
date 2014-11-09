#include "docxstyleheading.h"
#include "docxstyle.h"
namespace TDocx
{
AbsHeading::AbsHeading()
{

}

void AbsHeading::iniHeading()
{
    // heading 1
    StyleTagElement *head = new StyleTagElement(StyleType::paragraph, QString("Heading%1").arg(QString::number((int)headLevel())));
    TagElement *child = new TagElement(QStringLiteral("w:name"));
    child->addProperty(QStringLiteral("w:val"), QString("heading %1").arg(QString::number((int)headLevel())));
    head->addChild(child);

    child = new TagElement(QStringLiteral("w:basedOn"));
    child->addProperty(QStringLiteral("w:val"), QStringLiteral("Normal"));
    head->addChild(child);

    child = new TagElement(QStringLiteral("w:next"));
    child->addProperty(QStringLiteral("w:val"), QStringLiteral("Normal"));
    head->addChild(child);

    child = new TagElement(QStringLiteral("w:qFormat"));
    head->addChild(child);

    child = new TagElement(QStringLiteral("w:rsid"));
    child->addProperty(QStringLiteral("w:val"), QStringLiteral("00892A95"));
    head->addChild(child);

    //pPr
    ITagElement * pPrE = pPrElement();
    child->addChild(pPrE);


    child->addChild(rPrElement());

    head->addChild(child);
}

void AbsHeading::saveToXmlElement(QXmlStreamWriter *writer) const
{

}

void AbsHeading::addProperty(QString name, QString value)
{
}

void AbsHeading::addChild(ITagElement *child)
{
}

void AbsHeading::remoevChild(ITagElement *child)
{
}



// Heading1

Heading1::Heading1()
    : AbsHeading()
{

}

ITagElement *Heading1::pPrElement()
{
    // pPr
    TagElement *pPr = new TagElement(QStringLiteral("w:pPr"));
    TagElement* pPrchild = new TagElement(QStringLiteral("w:keepNext"));
    pPr->addChild(pPrchild);

    pPrchild = new TagElement(QStringLiteral("w:keepLines"));
    pPr->addChild(pPrchild);

    pPrchild = new TagElement(QStringLiteral("w:spacing"));
    pPrchild->addProperty(QStringLiteral("w:before"), QStringLiteral("340"));
    pPrchild->addProperty(QStringLiteral("w:after"), QStringLiteral("330"));
    pPrchild->addProperty(QStringLiteral("w:line"), QStringLiteral("578"));
    pPrchild->addProperty(QStringLiteral("w:lineRule"), QStringLiteral("auto"));

    pPrchild = new TagElement(QStringLiteral("w:outlineLvl"));
    pPrchild->addProperty(QStringLiteral("w:val"), QStringLiteral("0"));

    pPr->addChild(pPrchild);

    return pPr;
}

ITagElement *Heading1::rPrElement()
{
    //rPr
    TagElement *rPr = new TagElement(QStringLiteral("w:rPr"));
    TagElement* rPrchild = new TagElement(QStringLiteral("w:b"));
    rPr->addChild(rPrchild);

    rPrchild = new TagElement(QStringLiteral("w:bCs"));
    rPr->addChild(rPrchild);

    rPrchild = new TagElement(QStringLiteral("w:kern"));                // 字间距
    rPrchild->addProperty(QStringLiteral("w:val"), QStringLiteral("44"));

    rPrchild = new TagElement(QStringLiteral("w:sz"));
    rPrchild->addProperty(QStringLiteral("w:val"), QStringLiteral("44"));

    rPrchild = new TagElement(QStringLiteral("w:szCs"));
    rPrchild->addProperty(QStringLiteral("w:val"), QStringLiteral("44"));

    rPr->addChild(rPrchild);
    return rPr;
}

HeadingType Heading1::headLevel()
{
    return HeadingType::header1;
}

Heading2::Heading2()
{

}

ITagElement *Heading2::pPrElement()
{
    //pPr
    TagElement *child = new TagElement(QStringLiteral("w:pPr"));
    TagElement * pPrchild = new TagElement(QStringLiteral("w:keepNext"));
    child->addChild(pPrchild);

    pPrchild = new TagElement(QStringLiteral("w:keepLines"));
    child->addChild(pPrchild);

    pPrchild = new TagElement(QStringLiteral("w:spacing"));
    pPrchild->addProperty(QStringLiteral("w:before"), QStringLiteral("260"));
    pPrchild->addProperty(QStringLiteral("w:after"), QStringLiteral("260"));
    pPrchild->addProperty(QStringLiteral("w:line"), QStringLiteral("416"));
    pPrchild->addProperty(QStringLiteral("w:lineRule"), QStringLiteral("auto"));

    pPrchild = new TagElement(QStringLiteral("w:outlineLvl"));
    pPrchild->addProperty(QStringLiteral("w:val"), QStringLiteral("1"));

    child->addChild(pPrchild);
    return child;
}

ITagElement *Heading2::rPrElement()
{
    //rPr
    TagElement *child = new TagElement(QStringLiteral("w:rPr"));
    TagElement *rPrchild = new TagElement(QStringLiteral("w:b"));
    child->addChild(rPrchild);

    rPrchild = new TagElement(QStringLiteral("w:bCs"));
    child->addChild(rPrchild);

    rPrchild = new TagElement(QStringLiteral("w:sz"));
    rPrchild->addProperty(QStringLiteral("w:val"), QStringLiteral("32"));

    rPrchild = new TagElement(QStringLiteral("w:szCs"));
    rPrchild->addProperty(QStringLiteral("w:val"), QStringLiteral("32"));

    child->addChild(rPrchild);
    return child;
}

HeadingType Heading2::headLevel()
{
    return HeadingType::header2;
}

Heading3::Heading3()
{

}


ITagElement *Heading3::pPrElement()
{
    //pPr
    TagElement *child = new TagElement(QStringLiteral("w:pPr"));
    TagElement *pPrchild = new TagElement(QStringLiteral("w:keepNext"));
    child->addChild(pPrchild);

    pPrchild = new TagElement(QStringLiteral("w:keepLines"));
    child->addChild(pPrchild);

    pPrchild = new TagElement(QStringLiteral("w:spacing"));
    pPrchild->addProperty(QStringLiteral("w:before"), QStringLiteral("260"));
    pPrchild->addProperty(QStringLiteral("w:after"), QStringLiteral("260"));
    pPrchild->addProperty(QStringLiteral("w:line"), QStringLiteral("416"));
    pPrchild->addProperty(QStringLiteral("w:lineRule"), QStringLiteral("auto"));

    pPrchild = new TagElement(QStringLiteral("w:outlineLvl"));
    pPrchild->addProperty(QStringLiteral("w:val"), QStringLiteral("2"));

    child->addChild(pPrchild);
    return child;

}

ITagElement *Heading3::rPrElement()
{
    //rPr
    TagElement *child = new TagElement(QStringLiteral("w:rPr"));
    TagElement *rPrchild = new TagElement(QStringLiteral("w:b"));
    child->addChild(rPrchild);

    rPrchild = new TagElement(QStringLiteral("w:bCs"));
    child->addChild(rPrchild);

    //    rPrchild = new TagElement(QStringLiteral("w:kern"));                // 字间距
    //    rPrchild.addProperty(QStringLiteral("w:val"), QStringLiteral("44"));

    rPrchild = new TagElement(QStringLiteral("w:sz"));
    rPrchild->addProperty(QStringLiteral("w:val"), QStringLiteral("32"));

    rPrchild = new TagElement(QStringLiteral("w:szCs"));
    rPrchild->addProperty(QStringLiteral("w:val"), QStringLiteral("32"));

    child->addChild(rPrchild);
    return child;
}

HeadingType Heading3::headLevel()
{
    return HeadingType::header3;
}

// Heading 4
Heading4::Heading4()
{

}

ITagElement *Heading4::pPrElement()
{
    //pPr
    TagElement *child = new TagElement(QStringLiteral("w:pPr"));
    TagElement *pPrchild = new TagElement(QStringLiteral("w:keepNext"));
    child->addChild(pPrchild);

    pPrchild = new TagElement(QStringLiteral("w:keepLines"));
    child->addChild(pPrchild);

    pPrchild = new TagElement(QStringLiteral("w:spacing"));
    pPrchild->addProperty(QStringLiteral("w:before"), QStringLiteral("280"));
    pPrchild->addProperty(QStringLiteral("w:after"), QStringLiteral("290"));
    pPrchild->addProperty(QStringLiteral("w:line"), QStringLiteral("376"));
    pPrchild->addProperty(QStringLiteral("w:lineRule"), QStringLiteral("auto"));

    pPrchild = new TagElement(QStringLiteral("w:outlineLvl"));
    pPrchild->addProperty(QStringLiteral("w:val"), QStringLiteral("3"));

    child->addChild(pPrchild);
    return child;
}

ITagElement *Heading4::rPrElement()
{
    //rPr
    TagElement *child = new TagElement(QStringLiteral("w:rPr"));
    TagElement *rPrchild = new TagElement(QStringLiteral("w:b"));
    child->addChild(rPrchild);

    rPrchild = new TagElement(QStringLiteral("w:bCs"));
    child->addChild(rPrchild);

    //    rPrchild = new TagElement(QStringLiteral("w:kern"));                // 字间距
    //    rPrchild.addProperty(QStringLiteral("w:val"), QStringLiteral("44"));

    rPrchild = new TagElement(QStringLiteral("w:sz"));
    rPrchild->addProperty(QStringLiteral("w:val"), QStringLiteral("28"));

    rPrchild = new TagElement(QStringLiteral("w:szCs"));
    rPrchild->addProperty(QStringLiteral("w:val"), QStringLiteral("28"));

    child->addChild(rPrchild);
    return child;
}

HeadingType Heading4::headLevel()
{
    return HeadingType::header4;
}

TDocx::Heading5::Heading5()
{

}

ITagElement *Heading5::pPrElement()
{
    //pPr
    TagElement *child = new TagElement(QStringLiteral("w:pPr"));
    TagElement *pPrchild = new TagElement(QStringLiteral("w:keepNext"));
    child->addChild(pPrchild);

    pPrchild = new TagElement(QStringLiteral("w:keepLines"));
    child->addChild(pPrchild);

    pPrchild = new TagElement(QStringLiteral("w:spacing"));
    pPrchild->addProperty(QStringLiteral("w:before"), QStringLiteral("280"));
    pPrchild->addProperty(QStringLiteral("w:after"), QStringLiteral("290"));
    pPrchild->addProperty(QStringLiteral("w:line"), QStringLiteral("376"));
    pPrchild->addProperty(QStringLiteral("w:lineRule"), QStringLiteral("auto"));

    pPrchild = new TagElement(QStringLiteral("w:outlineLvl"));
    pPrchild->addProperty(QStringLiteral("w:val"), QStringLiteral("4"));

    child->addChild(pPrchild);
    return child;
}

ITagElement *Heading5::rPrElement()
{
    //rPr
    TagElement *child = new TagElement(QStringLiteral("w:rPr"));
    TagElement *rPrchild = new TagElement(QStringLiteral("w:b"));
    child->addChild(rPrchild);

    rPrchild = new TagElement(QStringLiteral("w:bCs"));
    child->addChild(rPrchild);

    //    rPrchild = new TagElement(QStringLiteral("w:kern"));                // 字间距
    //    rPrchild.addProperty(QStringLiteral("w:val"), QStringLiteral("44"));

    rPrchild = new TagElement(QStringLiteral("w:sz"));
    rPrchild->addProperty(QStringLiteral("w:val"), QStringLiteral("28"));

    rPrchild = new TagElement(QStringLiteral("w:szCs"));
    rPrchild->addProperty(QStringLiteral("w:val"), QStringLiteral("28"));

    child->addChild(rPrchild);
    return child;
}

HeadingType Heading5::headLevel()
{
    return HeadingType::header5;
}

// heading 6
Heading6::Heading6()
{

}

ITagElement *Heading6::pPrElement()
{
        //pPr
        TagElement *child = new TagElement(QStringLiteral("w:pPr"));
        TagElement *pPrchild = new TagElement(QStringLiteral("w:keepNext"));
        child->addChild(pPrchild);

        pPrchild = new TagElement(QStringLiteral("w:keepLines"));
        child->addChild(pPrchild);

        pPrchild = new TagElement(QStringLiteral("w:spacing"));
        pPrchild->addProperty(QStringLiteral("w:before"), QStringLiteral("240"));
        pPrchild->addProperty(QStringLiteral("w:after"), QStringLiteral("64"));
        pPrchild->addProperty(QStringLiteral("w:line"), QStringLiteral("320"));
        pPrchild->addProperty(QStringLiteral("w:lineRule"), QStringLiteral("auto"));

        pPrchild = new TagElement(QStringLiteral("w:outlineLvl"));
        pPrchild->addProperty(QStringLiteral("w:val"), QStringLiteral("5"));

        child->addChild(pPrchild);

    return child;
}

ITagElement *Heading6::rPrElement()
{
    //rPr
    TagElement *child = new TagElement(QStringLiteral("w:rPr"));
    TagElement *rPrchild = new TagElement(QStringLiteral("w:b"));
    child->addChild(rPrchild);

    rPrchild = new TagElement(QStringLiteral("w:bCs"));
    child->addChild(rPrchild);

    //    rPrchild = new TagElement(QStringLiteral("w:kern"));                // 字间距
    //    rPrchild.addProperty(QStringLiteral("w:val"), QStringLiteral("44"));

    rPrchild = new TagElement(QStringLiteral("w:sz"));
    rPrchild->addProperty(QStringLiteral("w:val"), QStringLiteral("24"));

    rPrchild = new TagElement(QStringLiteral("w:szCs"));
    rPrchild->addProperty(QStringLiteral("w:val"), QStringLiteral("24"));

    child->addChild(rPrchild);
    return child;
}

HeadingType Heading6::headLevel()
{
    return HeadingType::header6;
}

// Heading7
Heading7::Heading7()
{

}

ITagElement *Heading7::pPrElement()
{
    return nullptr;
}

ITagElement *Heading7::rPrElement()
{
    return nullptr;
}

HeadingType Heading7::headLevel()
{
    return HeadingType::header7;
}

}







