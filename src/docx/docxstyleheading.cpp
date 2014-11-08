#include "docxstyleheading.h"
#include "docxstyle.h"
namespace TDocx
{
AbsHeading::AbsHeading()
{
    // heading 1
    StyleTagElement *head = new StyleTagElement(StyleType::paragraph, QStringLiteral("Heading1"));
    TagElement *child = new TagElement(QStringLiteral("w:name"));
    child->addProperty(QStringLiteral("w:val"), QStringLiteral("heading 1"));
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
    child->addChild(pPrElement());
//    child = new TagElement(QStringLiteral("w:pPr"));
//    TagElement* pPrchild = new TagElement(QStringLiteral("w:keepNext"));
//    child.addChild(pPrchild);

//    pPrchild = new TagElement(QStringLiteral("w:keepLines"));
//    child.addChild(pPrchild);

//    pPrchild = new TagElement(QStringLiteral("w:spacing"));
//    pPrchild.addProperty(QStringLiteral("w:before"), QStringLiteral("340"));
//    pPrchild.addProperty(QStringLiteral("w:after"), QStringLiteral("330"));
//    pPrchild.addProperty(QStringLiteral("w:line"), QStringLiteral("578"));
//    pPrchild.addProperty(QStringLiteral("w:lineRule"), QStringLiteral("auto"));

//    pPrchild = new TagElement(QStringLiteral("w:outlineLvl"));
//    pPrchild.addProperty(QStringLiteral("w:val"), QStringLiteral("0"));

//    child.addChild(pPrchild);

//    child.addChild(pPrchild);

    child->addChild(rPrElement());
    //rPr
//    child = new TagElement(QStringLiteral("w:rPr"));
//    TagElement* rPrchild = new TagElement(QStringLiteral("w:b"));
//    child.addChild(rPrchild);

//    rPrchild = new TagElement(QStringLiteral("w:bCs"));
//    child.addChild(rPrchild);

//    rPrchild = new TagElement(QStringLiteral("w:kern"));                // 字间距
//    rPrchild.addProperty(QStringLiteral("w:val"), QStringLiteral("44"));

//    rPrchild = new TagElement(QStringLiteral("w:sz"));
//    rPrchild.addProperty(QStringLiteral("w:val"), QStringLiteral("44"));

//    rPrchild = new TagElement(QStringLiteral("w:szCs"));
//    rPrchild.addProperty(QStringLiteral("w:val"), QStringLiteral("44"));

//    child.addChild(rPrchild);

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

}


