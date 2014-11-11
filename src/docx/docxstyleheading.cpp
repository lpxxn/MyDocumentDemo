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
    m_head = new StyleTagElement(StyleType::paragraph, headId());
    TagElement *child = new TagElement(QStringLiteral("w:name"));
    child->addProperty(QStringLiteral("w:val"), QString("heading %1").arg(QString::number((int)headLevel())));
    m_head->addChild(child);

    child = new TagElement(QStringLiteral("w:basedOn"));
    child->addProperty(QStringLiteral("w:val"), QStringLiteral("Normal"));
    m_head->addChild(child);

    child = new TagElement(QStringLiteral("w:next"));
    child->addProperty(QStringLiteral("w:val"), QStringLiteral("Normal"));
    m_head->addChild(child);

    child = new TagElement(QStringLiteral("w:qFormat"));
    m_head->addChild(child);

    child = new TagElement(QStringLiteral("w:rsid"));
    child->addProperty(QStringLiteral("w:val"), QStringLiteral("00892A95"));
    m_head->addChild(child);

    //pPr
    ITagElement * pPrE = pPrElement();
    m_head->addChild(pPrE);

    // rPr
    m_head->addChild(rPrElement());

}

void AbsHeading::saveToXmlElement(QXmlStreamWriter *writer) const
{
    m_head->saveToXmlElement(writer);
}

void AbsHeading::addProperty(QString name, QString value)
{
    m_head->addProperty(name, value);
}

void AbsHeading::addChild(ISaveToXml *child)
{
    m_head->addChild(child);
}

void AbsHeading::remoevChild(ISaveToXml *child)
{
    m_head->remoevChild(child);
}

QString AbsHeading::headId() const
{
    return QString("Heading%1").arg(QString::number((int)headLevel()));
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
    pPr->addChild(pPrchild);

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
    rPr->addChild(rPrchild);

    rPrchild = new TagElement(QStringLiteral("w:sz"));
    rPrchild->addProperty(QStringLiteral("w:val"), QStringLiteral("44"));
    rPr->addChild(rPrchild);

    rPrchild = new TagElement(QStringLiteral("w:szCs"));
    rPrchild->addProperty(QStringLiteral("w:val"), QStringLiteral("44"));
    rPr->addChild(rPrchild);

    return rPr;
}

HeadingLevel Heading1::headLevel() const
{
    return HeadingLevel::head1;
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
    child->addChild(pPrchild);

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
    child->addChild(rPrchild);

    rPrchild = new TagElement(QStringLiteral("w:szCs"));
    rPrchild->addProperty(QStringLiteral("w:val"), QStringLiteral("32"));
    child->addChild(rPrchild);

    return child;
}

HeadingLevel Heading2::headLevel() const
{
    return HeadingLevel::head2;
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
    child->addChild(pPrchild);

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
    child->addChild(rPrchild);

    rPrchild = new TagElement(QStringLiteral("w:szCs"));
    rPrchild->addProperty(QStringLiteral("w:val"), QStringLiteral("32"));
    child->addChild(rPrchild);

    return child;
}

HeadingLevel Heading3::headLevel() const
{
    return HeadingLevel::head3;
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
    child->addChild(pPrchild);

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
    child->addChild(rPrchild);

    rPrchild = new TagElement(QStringLiteral("w:szCs"));
    rPrchild->addProperty(QStringLiteral("w:val"), QStringLiteral("28"));
    child->addChild(rPrchild);

    return child;
}

HeadingLevel Heading4::headLevel() const
{
    return HeadingLevel::head4;
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
    child->addChild(pPrchild);

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
    child->addChild(rPrchild);

    rPrchild = new TagElement(QStringLiteral("w:szCs"));
    rPrchild->addProperty(QStringLiteral("w:val"), QStringLiteral("28"));
    child->addChild(rPrchild);

    return child;
}

HeadingLevel Heading5::headLevel() const
{
    return HeadingLevel::head5;
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
    child->addChild(pPrchild);

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
    child->addChild(rPrchild);

    rPrchild = new TagElement(QStringLiteral("w:szCs"));
    rPrchild->addProperty(QStringLiteral("w:val"), QStringLiteral("24"));
    child->addChild(rPrchild);

    return child;
}

HeadingLevel Heading6::headLevel() const
{
    return HeadingLevel::head6;
}

// Heading7
Heading7::Heading7()
{

}

ITagElement *Heading7::pPrElement()
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
    child->addChild(pPrchild);

    pPrchild = new TagElement(QStringLiteral("w:outlineLvl"));
    pPrchild->addProperty(QStringLiteral("w:val"), QStringLiteral("6"));
    child->addChild(pPrchild);

    return child;
}

ITagElement *Heading7::rPrElement()
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
    child->addChild(rPrchild);

    rPrchild = new TagElement(QStringLiteral("w:szCs"));
    rPrchild->addProperty(QStringLiteral("w:val"), QStringLiteral("24"));
    child->addChild(rPrchild);

    return child;
}

HeadingLevel Heading7::headLevel() const
{
    return HeadingLevel::head7;
}

// head 8
Heading8::Heading8()
{

}

ITagElement *Heading8::pPrElement()
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
    child->addChild(pPrchild);

    pPrchild = new TagElement(QStringLiteral("w:outlineLvl"));
    pPrchild->addProperty(QStringLiteral("w:val"), QStringLiteral("7"));
    child->addChild(pPrchild);

    return child;
}

ITagElement *Heading8::rPrElement()
{
    //rPr
    TagElement *child = new TagElement(QStringLiteral("w:rPr"));

    TagElement *rPrchild = new TagElement(QStringLiteral("w:sz"));
    rPrchild->addProperty(QStringLiteral("w:val"), QStringLiteral("24"));
    child->addChild(rPrchild);

    rPrchild = new TagElement(QStringLiteral("w:szCs"));
    rPrchild->addProperty(QStringLiteral("w:val"), QStringLiteral("24"));
    child->addChild(rPrchild);

    return child;
}

HeadingLevel Heading8::headLevel() const
{
    return HeadingLevel::head8;
}

// head 9
Heading9::Heading9()
{

}

ITagElement *Heading9::pPrElement()
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
    child->addChild(pPrchild);

    pPrchild = new TagElement(QStringLiteral("w:outlineLvl"));
    pPrchild->addProperty(QStringLiteral("w:val"), QStringLiteral("8"));
    child->addChild(pPrchild);

    return child;
}

ITagElement *Heading9::rPrElement()
{
    //rPr
    TagElement *child = new TagElement(QStringLiteral("w:rPr"));

    TagElement *rPrchild = new TagElement(QStringLiteral("w:szCs"));
    rPrchild->addProperty(QStringLiteral("w:val"), QStringLiteral("21"));
    child->addChild(rPrchild);

    return child;
}

HeadingLevel Heading9::headLevel() const
{
    return HeadingLevel::head9;
}

AbsHeading *HeadingFactory::heading(HeadingLevel headLevel)
{
    AbsHeading *absHead;
    switch(headLevel) {
    case HeadingLevel::head1:
        absHead =  new Heading1();
        break;
    case HeadingLevel::head2:
        absHead =  new Heading2();
        break;
    case HeadingLevel::head3:
        absHead =  new Heading3();
        break;
    case HeadingLevel::head4:
        absHead =  new Heading4();
        break;
    case HeadingLevel::head5:
        absHead =  new Heading5();
        break;
    case HeadingLevel::head6:
        absHead =  new Heading6();
        break;
    case HeadingLevel::head7:
        absHead =  new Heading7();
        break;
    case HeadingLevel::head8:
        absHead =  new Heading8();
        break;
    case HeadingLevel::head9:
        absHead =  new Heading9();
        break;
    }
    absHead->iniHeading();
    return absHead;
}

}

