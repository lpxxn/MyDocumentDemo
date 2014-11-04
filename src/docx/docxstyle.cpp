#include "docxstyle.h"
#include <QXmlStreamWriter>

namespace TDocx
{
// begin StyleTagElement
StyleTagElement::StyleTagElement(StyleType type, const QString &styleId)
    : m_type(type), m_styleId(styleId)
{

}

void StyleTagElement::addProperty(QString name, QString value)
{
    m_properties.append(pairValue(name, value));
}

void StyleTagElement::addChild(ITagElement *child)
{
    m_childs.append(child);
}

void StyleTagElement::remoevChild(ITagElement *child)
{
    if (m_childs.contains(child)) {
        m_childs.removeOne(child);
        delete child;
        child = nullptr;
    }
}

void StyleTagElement::saveToXmlElement(QXmlStreamWriter *writer) const
{
    writer->writeStartElement("w:style");
    writer->writeAttribute(QStringLiteral("w:type"), convertType(m_type));
    writer->writeAttribute(QStringLiteral("w:styleId"), m_styleId);
    if (m_properties.count() > 0)
        for (pairValue att : m_properties) {
            writer->writeAttribute(att.first, att.second);
        }
    StyleTagIterator iter =  createIterator();
    while(iter.hasNext()) {
        ITagElement *element = iter.next();
        element->saveToXmlElement(writer);
    }
    writer->writeEndElement();// end style
}

StyleTagIterator StyleTagElement::createIterator() const
{
    return StyleTagIterator(this);
}

StyleTagElement::~StyleTagElement()
{
    StyleTagIterator iter =  createIterator();
    while(iter.hasNext()) {
        ITagElement *ele = iter.next();
        delete ele;
    }
    m_childs.clear();
}

QString StyleTagElement::convertType(StyleType type) const
{
    switch (type) {
    case StyleType::paragraph:
        return QStringLiteral("paragraph");
        break;
    case StyleType::character:
        return QStringLiteral("character");
        break;
    case StyleType::numbering:
        return QStringLiteral("numbering");
        break;
    case StyleType::table:
        return QStringLiteral("table");
        break;
    }
}
// end StyleTagElement

// begin StyleTagIterator
StyleTagIterator::StyleTagIterator(const StyleTagElement *element)
    : m_tagElement(element), m_currentIndex(0)
{
}

bool StyleTagIterator::hasNext() const
{
    return m_tagElement->m_childs.count() > 0 && m_currentIndex < m_tagElement->m_childs.size();
}

ITagElement *StyleTagIterator::next() const
{
    return m_tagElement->m_childs.at(m_currentIndex++);
}


// end StyleTagIterator


const QString mc = QStringLiteral("http://schemas.openxmlformats.org/markup-compatibility/2006");
const QString r = QStringLiteral("http://schemas.openxmlformats.org/officeDocument/2006/relationships");
const QString w = QStringLiteral("http://schemas.openxmlformats.org/wordprocessingml/2006/main");
const QString w14 = QStringLiteral("http://schemas.microsoft.com/office/word/2010/wordml");

DocxStyle::DocxStyle(CreateFlag flag)
    : AbstractOOXmlFile(flag)
{
    if (flag == CreateFlag::F_NewFromScratch)
        initTag();
}

void DocxStyle::saveToXmlFile(QIODevice *device) const
{
    QXmlStreamWriter writer(device);
    writer.writeStartDocument(QStringLiteral("1.0"), true);
    writer.writeStartElement("w:styles");
    writer.writeNamespace(mc, QStringLiteral("mc"));
    writer.writeNamespace(r, QStringLiteral("r"));
    writer.writeNamespace(w, QStringLiteral("w"));
    writer.writeNamespace(w14, QStringLiteral("w14"));
    writer.writeAttribute(mc, QStringLiteral("Ignorable"), QStringLiteral("w14"));

    writer.writeEndElement();
    writer.writeEndDocument();
}

bool DocxStyle::loadFromXmlFile(QIODevice *device)
{
    return true;
}

void DocxStyle::initTag()
{
    TagElement *element = new TagElement(QStringLiteral("w:docDefaults"));
    TagElement *rprDefChild = new TagElement(QStringLiteral("w:rPrDefault"));
    TagElement *rPrChild = new TagElement(QStringLiteral("w:rPr"));

    TagElement *rFontsChild = new TagElement(QStringLiteral("w:rFonts"));
    rFontsChild->addProperty(QStringLiteral("w:asciiTheme"), QStringLiteral("minorHAnsi"));
    rFontsChild->addProperty(QStringLiteral("w:eastAsiaTheme"), QStringLiteral("minorEastAsia"));
    rFontsChild->addProperty(QStringLiteral("w:hAnsiTheme"), QStringLiteral("minorHAnsi"));
    rFontsChild->addProperty(QStringLiteral("w:cstheme"), QStringLiteral("minorBidi"));
    rPrChild->addChild(rFontsChild);

    TagElement *kernChild = new TagElement(QStringLiteral("w:kern"));
    kernChild->addProperty(QStringLiteral("w:val"), QStringLiteral("2"));
    rPrChild->addChild(kernChild);

    TagElement *szChild = new TagElement(QStringLiteral("w:sz"));
    szChild->addProperty(QStringLiteral("w:val"), QStringLiteral("21"));
    rPrChild->addChild(szChild);

    TagElement *szCsChild = new TagElement(QStringLiteral("w:szCs"));
    szCsChild->addProperty(QStringLiteral("w:val"), QStringLiteral("22"));
    rPrChild->addChild(szCsChild);

    TagElement *langChild = new TagElement(QStringLiteral("w:szCs"));
    langChild->addProperty(QStringLiteral("w:val"), QStringLiteral("en-US"));
    langChild->addProperty(QStringLiteral("w:eastAsia"), QStringLiteral("zh-CN"));
    langChild->addProperty(QStringLiteral("w:bidi"), QStringLiteral("ar-SA"));
    rPrChild->addChild(langChild);

    rprDefChild->addChild(rPrChild);
    element->addChild(rprDefChild);
    m_childs.append(element);
    // end docDefaults


    element = new TagElement(QStringLiteral("w:latentStyles"));
    element->addProperty(QStringLiteral("w:defLockedState"), QStringLiteral("0"));
    element->addProperty(QStringLiteral("w:defUIPriority"), QStringLiteral("99"));
    element->addProperty(QStringLiteral("w:defSemiHidden"), QStringLiteral("1"));
    element->addProperty(QStringLiteral("w:defUnhideWhenUsed"), QStringLiteral("1"));
    element->addProperty(QStringLiteral("w:defQFormat"), QStringLiteral("0"));
    element->addProperty(QStringLiteral("w:count"), QStringLiteral("267"));

    TagElement *child = new TagElement(QStringLiteral("w:lsdException"));
    child->addProperty(QStringLiteral("w:name"), QStringLiteral("Normal"));
    child->addProperty(QStringLiteral("w:semiHidden"), QStringLiteral("0"));
    child->addProperty(QStringLiteral("w:uiPriority"), QStringLiteral("0"));
    child->addProperty(QStringLiteral("w:unhideWhenUsed"), QStringLiteral("0"));
    child->addProperty(QStringLiteral("w:qFormat"), QStringLiteral("1"));
    element->addChild(child);

    child = new TagElement(QStringLiteral("w:lsdException"));
    child->addProperty(QStringLiteral("w:name"), QStringLiteral("heading 1"));
    child->addProperty(QStringLiteral("w:semiHidden"), QStringLiteral("0"));
    child->addProperty(QStringLiteral("w:uiPriority"), QStringLiteral("9"));
    child->addProperty(QStringLiteral("w:unhideWhenUsed"), QStringLiteral("0"));
    child->addProperty(QStringLiteral("w:qFormat"), QStringLiteral("1"));
    element->addChild(child);
    // header 2 to 9
    for (int i = 2; i < 10; i++) {
        child = new TagElement(QStringLiteral("w:lsdException"));
        child->addProperty(QStringLiteral("w:name"), QString("heading %1").arg(QString::number(i)));
        child->addProperty(QStringLiteral("w:uiPriority"), QStringLiteral("9"));
        child->addProperty(QStringLiteral("w:qFormat"), QStringLiteral("1"));
        element->addChild(child);
    }

    // toc 2 to 9
    for (int i = 2; i < 10; i++) {
        child = new TagElement(QStringLiteral("w:lsdException"));
        child->addProperty(QStringLiteral("w:name"), QString("toc %1").arg(QString::number(i)));
        child->addProperty(QStringLiteral("w:uiPriority"), QStringLiteral("39"));
        element->addChild(child);
    }

    child = new TagElement(QStringLiteral("w:lsdException"));
    child->addProperty(QStringLiteral("w:name"), QStringLiteral("caption"));
    child->addProperty(QStringLiteral("w:uiPriority"), QStringLiteral("35"));
    child->addProperty(QStringLiteral("w:qFormat"), QStringLiteral("1"));
    element->addChild(child);

    child = new TagElement(QStringLiteral("w:lsdException"));
    child->addProperty(QStringLiteral("w:name"), QStringLiteral("Title"));
    child->addProperty(QStringLiteral("w:semiHidden"), QStringLiteral("0"));
    child->addProperty(QStringLiteral("w:uiPriority"), QStringLiteral("10"));
    child->addProperty(QStringLiteral("w:unhideWhenUsed"), QStringLiteral("0"));
    child->addProperty(QStringLiteral("w:qFormat"), QStringLiteral("1"));
    element->addChild(child);

    // Default Paragraph Font
    child = new TagElement(QStringLiteral("w:lsdException"));
    child->addProperty(QStringLiteral("w:name"), QStringLiteral("Default Paragraph Font"));
    child->addProperty(QStringLiteral("w:uiPriority"), QStringLiteral("1"));
    element->addChild(child);

    // Subtitle
    child = new TagElement(QStringLiteral("w:lsdException"));
    child->addProperty(QStringLiteral("w:name"), QStringLiteral("Strong"));
    child->addProperty(QStringLiteral("w:semiHidden"), QStringLiteral("0"));
    child->addProperty(QStringLiteral("w:uiPriority"), QStringLiteral("22"));
    child->addProperty(QStringLiteral("w:unhideWhenUsed"), QStringLiteral("0"));
    child->addProperty(QStringLiteral("w:qFormat"), QStringLiteral("1"));
    element->addChild(child);

    // Emphasis
    child = new TagElement(QStringLiteral("w:lsdException"));
    child->addProperty(QStringLiteral("w:name"), QStringLiteral("Emphasis"));
    child->addProperty(QStringLiteral("w:semiHidden"), QStringLiteral("0"));
    child->addProperty(QStringLiteral("w:uiPriority"), QStringLiteral("20"));
    child->addProperty(QStringLiteral("w:unhideWhenUsed"), QStringLiteral("0"));
    child->addProperty(QStringLiteral("w:qFormat"), QStringLiteral("1"));
    element->addChild(child);

    // Table Grid
    child = new TagElement(QStringLiteral("w:lsdException"));
    child->addProperty(QStringLiteral("w:name"), QStringLiteral("Table Grid"));
    child->addProperty(QStringLiteral("w:semiHidden"), QStringLiteral("0"));
    child->addProperty(QStringLiteral("w:uiPriority"), QStringLiteral("59"));
    child->addProperty(QStringLiteral("w:unhideWhenUsed"), QStringLiteral("0"));
    element->addChild(child);

    // Placeholder Text
    child = new TagElement(QStringLiteral("w:lsdException"));
    child->addProperty(QStringLiteral("w:name"), QStringLiteral("Placeholder Text"));
    child->addProperty(QStringLiteral("w:unhideWhenUsed"), QStringLiteral("0"));
    element->addChild(child);

    // No Spacing
    child = new TagElement(QStringLiteral("w:lsdException"));
    child->addProperty(QStringLiteral("w:name"), QStringLiteral("No Spacing"));
    child->addProperty(QStringLiteral("w:semiHidden"), QStringLiteral("0"));
    child->addProperty(QStringLiteral("w:uiPriority"), QStringLiteral("1"));
    child->addProperty(QStringLiteral("w:unhideWhenUsed"), QStringLiteral("0"));
    child->addProperty(QStringLiteral("w:qFormat"), QStringLiteral("1"));
    element->addChild(child);

    // Light Shading
    child = new TagElement(QStringLiteral("w:lsdException"));
    child->addProperty(QStringLiteral("w:name"), QStringLiteral("Light Shading"));
    child->addProperty(QStringLiteral("w:semiHidden"), QStringLiteral("0"));
    child->addProperty(QStringLiteral("w:uiPriority"), QStringLiteral("60"));
    child->addProperty(QStringLiteral("w:unhideWhenUsed"), QStringLiteral("0"));
    element->addChild(child);

    // Light List
    child = new TagElement(QStringLiteral("w:lsdException"));
    child->addProperty(QStringLiteral("w:name"), QStringLiteral("Light List"));
    child->addProperty(QStringLiteral("w:semiHidden"), QStringLiteral("0"));
    child->addProperty(QStringLiteral("w:uiPriority"), QStringLiteral("61"));
    child->addProperty(QStringLiteral("w:unhideWhenUsed"), QStringLiteral("0"));
    element->addChild(child);

    // Light Grid
    child = new TagElement(QStringLiteral("w:lsdException"));
    child->addProperty(QStringLiteral("w:name"), QStringLiteral("Light Grid"));
    child->addProperty(QStringLiteral("w:semiHidden"), QStringLiteral("0"));
    child->addProperty(QStringLiteral("w:uiPriority"), QStringLiteral("62"));
    child->addProperty(QStringLiteral("w:unhideWhenUsed"), QStringLiteral("0"));
    element->addChild(child);

    // Medium Shading 1 to 2
    int mediumIndex = 63;
    for (int i = 1; i < 3; i++) {
        child = new TagElement(QStringLiteral("w:lsdException"));
        child->addProperty(QStringLiteral("w:name"), QString("Medium Shading %1").arg(QString::number(i)));
        child->addProperty(QStringLiteral("w:semiHidden"), QStringLiteral("0"));
        child->addProperty(QStringLiteral("w:uiPriority"), QString::number(mediumIndex++));
        child->addProperty(QStringLiteral("w:unhideWhenUsed"), QStringLiteral("0"));
        element->addChild(child);
    }

    // Medium List 1 to 2
    for (int i = 1; i < 3; i++) {
        child = new TagElement(QStringLiteral("w:lsdException"));
        child->addProperty(QStringLiteral("w:name"), QString("Medium List %1").arg(QString::number(i)));
        child->addProperty(QStringLiteral("w:semiHidden"), QStringLiteral("0"));
        child->addProperty(QStringLiteral("w:uiPriority"), QString::number(mediumIndex++));
        child->addProperty(QStringLiteral("w:unhideWhenUsed"), QStringLiteral("0"));
        element->addChild(child);
    }

    // Medium Grid 1 to 3
    for (int i = 1; i < 4; i++) {
        child = new TagElement(QStringLiteral("w:lsdException"));
        child->addProperty(QStringLiteral("w:name"), QString("Medium Grid %1").arg(QString::number(i)));
        child->addProperty(QStringLiteral("w:semiHidden"), QStringLiteral("0"));
        child->addProperty(QStringLiteral("w:uiPriority"), QString::number(mediumIndex++));
        child->addProperty(QStringLiteral("w:unhideWhenUsed"), QStringLiteral("0"));
        element->addChild(child);
    }

    //
    child = new TagElement(QStringLiteral("w:lsdException"));
    child->addProperty(QStringLiteral("w:name"), QStringLiteral("caption"));
    child->addProperty(QStringLiteral("w:semiHidden"), QStringLiteral("0"));
    child->addProperty(QStringLiteral("w:uiPriority"), QStringLiteral("9"));
    child->addProperty(QStringLiteral("w:unhideWhenUsed"), QStringLiteral("0"));
    child->addProperty(QStringLiteral("w:qFormat"), QStringLiteral("1"));
    element->addChild(child);



    m_childs.append(element);
}




}


