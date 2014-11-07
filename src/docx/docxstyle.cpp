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

const QString mlatentStyle = R"~(<w:latentStyles w:defLockedState="0" w:defUIPriority="99" w:defSemiHidden="1" w:defUnhideWhenUsed="1" w:defQFormat="0" w:count="267">
        <w:lsdException w:name="Normal" w:semiHidden="0" w:uiPriority="0" w:unhideWhenUsed="0" w:qFormat="1"/>
        <w:lsdException w:name="heading 1" w:semiHidden="0" w:uiPriority="9" w:unhideWhenUsed="0" w:qFormat="1"/>
        <w:lsdException w:name="heading 2" w:uiPriority="9" w:qFormat="1"/>
        <w:lsdException w:name="heading 3" w:uiPriority="9" w:qFormat="1"/>
        <w:lsdException w:name="heading 4" w:uiPriority="9" w:qFormat="1"/>
        <w:lsdException w:name="heading 5" w:uiPriority="9" w:qFormat="1"/>
        <w:lsdException w:name="heading 6" w:uiPriority="9" w:qFormat="1"/>
        <w:lsdException w:name="heading 7" w:uiPriority="9" w:qFormat="1"/>
        <w:lsdException w:name="heading 8" w:uiPriority="9" w:qFormat="1"/>
        <w:lsdException w:name="heading 9" w:uiPriority="9" w:qFormat="1"/>
        <w:lsdException w:name="toc 1" w:uiPriority="39"/>
        <w:lsdException w:name="toc 2" w:uiPriority="39"/>
        <w:lsdException w:name="toc 3" w:uiPriority="39"/>
        <w:lsdException w:name="toc 4" w:uiPriority="39"/>
        <w:lsdException w:name="toc 5" w:uiPriority="39"/>
        <w:lsdException w:name="toc 6" w:uiPriority="39"/>
        <w:lsdException w:name="toc 7" w:uiPriority="39"/>
        <w:lsdException w:name="toc 8" w:uiPriority="39"/>
        <w:lsdException w:name="toc 9" w:uiPriority="39"/>
        <w:lsdException w:name="caption" w:uiPriority="35" w:qFormat="1"/>
        <w:lsdException w:name="Title" w:semiHidden="0" w:uiPriority="10" w:unhideWhenUsed="0" w:qFormat="1"/>
        <w:lsdException w:name="Default Paragraph Font" w:uiPriority="1"/>
        <w:lsdException w:name="Subtitle" w:semiHidden="0" w:uiPriority="11" w:unhideWhenUsed="0" w:qFormat="1"/>
        <w:lsdException w:name="Strong" w:semiHidden="0" w:uiPriority="22" w:unhideWhenUsed="0" w:qFormat="1"/>
        <w:lsdException w:name="Emphasis" w:semiHidden="0" w:uiPriority="20" w:unhideWhenUsed="0" w:qFormat="1"/>
        <w:lsdException w:name="Table Grid" w:semiHidden="0" w:uiPriority="59" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Placeholder Text" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="No Spacing" w:semiHidden="0" w:uiPriority="1" w:unhideWhenUsed="0" w:qFormat="1"/>
        <w:lsdException w:name="Light Shading" w:semiHidden="0" w:uiPriority="60" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Light List" w:semiHidden="0" w:uiPriority="61" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Light Grid" w:semiHidden="0" w:uiPriority="62" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Medium Shading 1" w:semiHidden="0" w:uiPriority="63" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Medium Shading 2" w:semiHidden="0" w:uiPriority="64" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Medium List 1" w:semiHidden="0" w:uiPriority="65" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Medium List 2" w:semiHidden="0" w:uiPriority="66" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Medium Grid 1" w:semiHidden="0" w:uiPriority="67" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Medium Grid 2" w:semiHidden="0" w:uiPriority="68" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Medium Grid 3" w:semiHidden="0" w:uiPriority="69" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Dark List" w:semiHidden="0" w:uiPriority="70" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Colorful Shading" w:semiHidden="0" w:uiPriority="71" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Colorful List" w:semiHidden="0" w:uiPriority="72" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Colorful Grid" w:semiHidden="0" w:uiPriority="73" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Light Shading Accent 1" w:semiHidden="0" w:uiPriority="60" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Light List Accent 1" w:semiHidden="0" w:uiPriority="61" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Light Grid Accent 1" w:semiHidden="0" w:uiPriority="62" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Medium Shading 1 Accent 1" w:semiHidden="0" w:uiPriority="63" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Medium Shading 2 Accent 1" w:semiHidden="0" w:uiPriority="64" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Medium List 1 Accent 1" w:semiHidden="0" w:uiPriority="65" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Revision" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="List Paragraph" w:semiHidden="0" w:uiPriority="34" w:unhideWhenUsed="0" w:qFormat="1"/>
        <w:lsdException w:name="Quote" w:semiHidden="0" w:uiPriority="29" w:unhideWhenUsed="0" w:qFormat="1"/>
        <w:lsdException w:name="Intense Quote" w:semiHidden="0" w:uiPriority="30" w:unhideWhenUsed="0" w:qFormat="1"/>
        <w:lsdException w:name="Medium List 2 Accent 1" w:semiHidden="0" w:uiPriority="66" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Medium Grid 1 Accent 1" w:semiHidden="0" w:uiPriority="67" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Medium Grid 2 Accent 1" w:semiHidden="0" w:uiPriority="68" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Medium Grid 3 Accent 1" w:semiHidden="0" w:uiPriority="69" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Dark List Accent 1" w:semiHidden="0" w:uiPriority="70" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Colorful Shading Accent 1" w:semiHidden="0" w:uiPriority="71" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Colorful List Accent 1" w:semiHidden="0" w:uiPriority="72" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Colorful Grid Accent 1" w:semiHidden="0" w:uiPriority="73" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Light Shading Accent 2" w:semiHidden="0" w:uiPriority="60" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Light List Accent 2" w:semiHidden="0" w:uiPriority="61" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Light Grid Accent 2" w:semiHidden="0" w:uiPriority="62" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Medium Shading 1 Accent 2" w:semiHidden="0" w:uiPriority="63" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Medium Shading 2 Accent 2" w:semiHidden="0" w:uiPriority="64" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Medium List 1 Accent 2" w:semiHidden="0" w:uiPriority="65" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Medium List 2 Accent 2" w:semiHidden="0" w:uiPriority="66" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Medium Grid 1 Accent 2" w:semiHidden="0" w:uiPriority="67" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Medium Grid 2 Accent 2" w:semiHidden="0" w:uiPriority="68" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Medium Grid 3 Accent 2" w:semiHidden="0" w:uiPriority="69" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Dark List Accent 2" w:semiHidden="0" w:uiPriority="70" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Colorful Shading Accent 2" w:semiHidden="0" w:uiPriority="71" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Colorful List Accent 2" w:semiHidden="0" w:uiPriority="72" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Colorful Grid Accent 2" w:semiHidden="0" w:uiPriority="73" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Light Shading Accent 3" w:semiHidden="0" w:uiPriority="60" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Light List Accent 3" w:semiHidden="0" w:uiPriority="61" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Light Grid Accent 3" w:semiHidden="0" w:uiPriority="62" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Medium Shading 1 Accent 3" w:semiHidden="0" w:uiPriority="63" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Medium Shading 2 Accent 3" w:semiHidden="0" w:uiPriority="64" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Medium List 1 Accent 3" w:semiHidden="0" w:uiPriority="65" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Medium List 2 Accent 3" w:semiHidden="0" w:uiPriority="66" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Medium Grid 1 Accent 3" w:semiHidden="0" w:uiPriority="67" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Medium Grid 2 Accent 3" w:semiHidden="0" w:uiPriority="68" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Medium Grid 3 Accent 3" w:semiHidden="0" w:uiPriority="69" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Dark List Accent 3" w:semiHidden="0" w:uiPriority="70" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Colorful Shading Accent 3" w:semiHidden="0" w:uiPriority="71" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Colorful List Accent 3" w:semiHidden="0" w:uiPriority="72" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Colorful Grid Accent 3" w:semiHidden="0" w:uiPriority="73" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Light Shading Accent 4" w:semiHidden="0" w:uiPriority="60" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Light List Accent 4" w:semiHidden="0" w:uiPriority="61" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Light Grid Accent 4" w:semiHidden="0" w:uiPriority="62" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Medium Shading 1 Accent 4" w:semiHidden="0" w:uiPriority="63" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Medium Shading 2 Accent 4" w:semiHidden="0" w:uiPriority="64" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Medium List 1 Accent 4" w:semiHidden="0" w:uiPriority="65" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Medium List 2 Accent 4" w:semiHidden="0" w:uiPriority="66" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Medium Grid 1 Accent 4" w:semiHidden="0" w:uiPriority="67" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Medium Grid 2 Accent 4" w:semiHidden="0" w:uiPriority="68" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Medium Grid 3 Accent 4" w:semiHidden="0" w:uiPriority="69" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Dark List Accent 4" w:semiHidden="0" w:uiPriority="70" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Colorful Shading Accent 4" w:semiHidden="0" w:uiPriority="71" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Colorful List Accent 4" w:semiHidden="0" w:uiPriority="72" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Colorful Grid Accent 4" w:semiHidden="0" w:uiPriority="73" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Light Shading Accent 5" w:semiHidden="0" w:uiPriority="60" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Light List Accent 5" w:semiHidden="0" w:uiPriority="61" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Light Grid Accent 5" w:semiHidden="0" w:uiPriority="62" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Medium Shading 1 Accent 5" w:semiHidden="0" w:uiPriority="63" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Medium Shading 2 Accent 5" w:semiHidden="0" w:uiPriority="64" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Medium List 1 Accent 5" w:semiHidden="0" w:uiPriority="65" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Medium List 2 Accent 5" w:semiHidden="0" w:uiPriority="66" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Medium Grid 1 Accent 5" w:semiHidden="0" w:uiPriority="67" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Medium Grid 2 Accent 5" w:semiHidden="0" w:uiPriority="68" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Medium Grid 3 Accent 5" w:semiHidden="0" w:uiPriority="69" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Dark List Accent 5" w:semiHidden="0" w:uiPriority="70" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Colorful Shading Accent 5" w:semiHidden="0" w:uiPriority="71" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Colorful List Accent 5" w:semiHidden="0" w:uiPriority="72" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Colorful Grid Accent 5" w:semiHidden="0" w:uiPriority="73" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Light Shading Accent 6" w:semiHidden="0" w:uiPriority="60" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Light List Accent 6" w:semiHidden="0" w:uiPriority="61" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Light Grid Accent 6" w:semiHidden="0" w:uiPriority="62" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Medium Shading 1 Accent 6" w:semiHidden="0" w:uiPriority="63" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Medium Shading 2 Accent 6" w:semiHidden="0" w:uiPriority="64" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Medium List 1 Accent 6" w:semiHidden="0" w:uiPriority="65" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Medium List 2 Accent 6" w:semiHidden="0" w:uiPriority="66" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Medium Grid 1 Accent 6" w:semiHidden="0" w:uiPriority="67" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Medium Grid 2 Accent 6" w:semiHidden="0" w:uiPriority="68" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Medium Grid 3 Accent 6" w:semiHidden="0" w:uiPriority="69" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Dark List Accent 6" w:semiHidden="0" w:uiPriority="70" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Colorful Shading Accent 6" w:semiHidden="0" w:uiPriority="71" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Colorful List Accent 6" w:semiHidden="0" w:uiPriority="72" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Colorful Grid Accent 6" w:semiHidden="0" w:uiPriority="73" w:unhideWhenUsed="0"/>
        <w:lsdException w:name="Subtle Emphasis" w:semiHidden="0" w:uiPriority="19" w:unhideWhenUsed="0" w:qFormat="1"/>
        <w:lsdException w:name="Intense Emphasis" w:semiHidden="0" w:uiPriority="21" w:unhideWhenUsed="0" w:qFormat="1"/>
        <w:lsdException w:name="Subtle Reference" w:semiHidden="0" w:uiPriority="31" w:unhideWhenUsed="0" w:qFormat="1"/>
        <w:lsdException w:name="Intense Reference" w:semiHidden="0" w:uiPriority="32" w:unhideWhenUsed="0" w:qFormat="1"/>
        <w:lsdException w:name="Book Title" w:semiHidden="0" w:uiPriority="33" w:unhideWhenUsed="0" w:qFormat="1"/>
        <w:lsdException w:name="Bibliography" w:uiPriority="37"/>
        <w:lsdException w:name="TOC Heading" w:uiPriority="39" w:qFormat="1"/>
        </w:latentStyles>)~";

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
    m_docDefaultsTag->saveToXmlElement(&writer);
    device->write(mlatentStyle.toUtf8());
    m_defParagraph->saveToXmlElement(&writer);
    m_defCharacter->saveToXmlElement(&writer);
    m_defTable->saveToXmlElement(&writer);
    m_defnumbering->saveToXmlElement(&writer);
    writer.writeEndElement();
    writer.writeEndDocument();
}

bool DocxStyle::loadFromXmlFile(QIODevice *device)
{
    return true;
}

void DocxStyle::initTag()
{
    m_docDefaultsTag = new TagElement(QStringLiteral("w:docDefaults"));
    TagElement *rprDefChild = new TagElement(QStringLiteral("w:rPrDefault"));
    TagElement *rPrChild = new TagElement(QStringLiteral("w:rPr"));

    TagElement *rFontsChild = new TagElement(QStringLiteral("w:rFonts"));
    rFontsChild->addProperty(QStringLiteral("w:asciiTheme"), QStringLiteral("minorHAnsi"));
    rFontsChild->addProperty(QStringLiteral("w:eastAsiaTheme"), QStringLiteral("minorEastAsia"));
    rFontsChild->addProperty(QStringLiteral("w:hAnsiTheme"), QStringLiteral("minorHAnsi"));
    rFontsChild->addProperty(QStringLiteral("w:cstheme"), QStringLiteral("minorBidi"));
    rPrChild->addChild(rFontsChild);

//    TagElement *kernChild = new TagElement(QStringLiteral("w:kern"));
//    kernChild->addProperty(QStringLiteral("w:val"), QStringLiteral("2"));
//    rPrChild->addChild(kernChild);

//    TagElement *szChild = new TagElement(QStringLiteral("w:sz"));
//    szChild->addProperty(QStringLiteral("w:val"), QStringLiteral("21"));
//    rPrChild->addChild(szChild);

//    TagElement *szCsChild = new TagElement(QStringLiteral("w:szCs"));
//    szCsChild->addProperty(QStringLiteral("w:val"), QStringLiteral("22"));
//    rPrChild->addChild(szCsChild);

//    TagElement *langChild = new TagElement(QStringLiteral("w:lang"));
//    langChild->addProperty(QStringLiteral("w:val"), QStringLiteral("en-US"));
//    langChild->addProperty(QStringLiteral("w:eastAsia"), QStringLiteral("zh-CN"));
//    langChild->addProperty(QStringLiteral("w:bidi"), QStringLiteral("ar-SA"));
//    rPrChild->addChild(langChild);

    rprDefChild->addChild(rPrChild);
    m_docDefaultsTag->addChild(rprDefChild);
    rprDefChild = new TagElement(QStringLiteral("w:pPrDefault"));
    m_docDefaultsTag->addChild(rprDefChild);
    // end docDefaults

    // m_defParagraph
    m_defParagraph = new StyleTagElement(StyleTagElement::StyleType::paragraph, QStringLiteral("a"));
    m_defParagraph->addProperty(QStringLiteral("w:default"), QStringLiteral("1"));

    TagElement *child  = new TagElement(QStringLiteral("w:name"));
    child->addProperty(QStringLiteral("w:val"), QStringLiteral("Normal"));
    m_defParagraph->addChild(child);

    child  = new TagElement(QStringLiteral("w:qFormat"));
    m_defParagraph->addChild(child);

    child  = new TagElement(QStringLiteral("w:pPr"));

    TagElement *childw = new TagElement(QStringLiteral("w:sz"));
    childw->addProperty(QStringLiteral("w:val"), QStringLiteral("24"));
    child->addChild(childw);
    childw = new TagElement(QStringLiteral("w:szCs"));
    childw->addProperty(QStringLiteral("w:val"), QStringLiteral("24"));
    child->addChild(childw);

    m_defParagraph->addChild(child);


    // m_defCharacter
    m_defCharacter = new StyleTagElement(StyleTagElement::StyleType::character, QStringLiteral("a0"));
    m_defCharacter->addProperty(QStringLiteral("w:default"), QStringLiteral("1"));

    child  = new TagElement(QStringLiteral("w:name"));
    child->addProperty(QStringLiteral("w:val"), QStringLiteral("Default Paragraph Font"));
    m_defCharacter->addChild(child);

    child  = new TagElement(QStringLiteral("w:uiPriority"));
    child->addProperty(QStringLiteral("w:val"), QStringLiteral("1"));
    m_defCharacter->addChild(child);

    child  = new TagElement(QStringLiteral("w:semiHidden"));
    m_defCharacter->addChild(child);

    child  = new TagElement(QStringLiteral("w:unhideWhenUsed"));
    m_defCharacter->addChild(child);

    // m_defTable
    m_defTable = new StyleTagElement(StyleTagElement::StyleType::table, QStringLiteral("a1"));
    m_defTable->addProperty(QStringLiteral("w:default"), QStringLiteral("1"));
    child  = new TagElement(QStringLiteral("w:name"));
    child->addProperty(QStringLiteral("w:val"), QStringLiteral("Normal Table"));
    m_defTable->addChild(child);

    child  = new TagElement(QStringLiteral("w:uiPriority"));
    child->addProperty(QStringLiteral("w:val"), QStringLiteral("99"));
    m_defTable->addChild(child);

    child  = new TagElement(QStringLiteral("w:semiHidden"));
    m_defTable->addChild(child);

    child  = new TagElement(QStringLiteral("w:unhideWhenUsed"));
    m_defTable->addChild(child);

    child  = new TagElement(QStringLiteral("w:tblPr"));
    TagElement *tblChild = new TagElement(QStringLiteral("w:tblInd"));
    tblChild->addProperty(QStringLiteral("w:w"), QStringLiteral("0"));
    tblChild->addProperty(QStringLiteral("w:type"), QStringLiteral("dxa"));
    child->addChild(tblChild);

    // cell
    tblChild = new TagElement(QStringLiteral("w:tblCellMar"));
    TagElement *cellChild = new TagElement(QStringLiteral("w:top"));
    cellChild->addProperty(QStringLiteral("w:w"), QStringLiteral("0"));
    cellChild->addProperty(QStringLiteral("w:type"), QStringLiteral("dxa"));
    tblChild->addChild(cellChild);

    cellChild = new TagElement(QStringLiteral("w:left"));
    cellChild->addProperty(QStringLiteral("w:w"), QStringLiteral("108"));
    cellChild->addProperty(QStringLiteral("w:type"), QStringLiteral("dxa"));
    tblChild->addChild(cellChild);

    cellChild = new TagElement(QStringLiteral("w:bottom"));
    cellChild->addProperty(QStringLiteral("w:w"), QStringLiteral("0"));
    cellChild->addProperty(QStringLiteral("w:type"), QStringLiteral("dxa"));
    tblChild->addChild(cellChild);

    cellChild = new TagElement(QStringLiteral("w:right"));
    cellChild->addProperty(QStringLiteral("w:w"), QStringLiteral("108"));
    cellChild->addProperty(QStringLiteral("w:type"), QStringLiteral("dxa"));
    tblChild->addChild(cellChild);

    child->addChild(tblChild);

    m_defTable->addChild(child);


    // m_defnumbering
    m_defnumbering = new StyleTagElement(StyleTagElement::StyleType::numbering, QStringLiteral("a2"));
    m_defnumbering->addProperty(QStringLiteral("w:default"), QStringLiteral("1"));

    child  = new TagElement(QStringLiteral("w:name"));
    child->addProperty(QStringLiteral("w:val"), QStringLiteral("No List"));
    m_defnumbering->addChild(child);

    child  = new TagElement(QStringLiteral("w:uiPriority"));
    child->addProperty(QStringLiteral("w:val"), QStringLiteral("99"));
    m_defnumbering->addChild(child);

    child  = new TagElement(QStringLiteral("w:semiHidden"));
    m_defnumbering->addChild(child);

    child  = new TagElement(QStringLiteral("w:unhideWhenUsed"));
    m_defnumbering->addChild(child);

}
QVector<StyleTagElement *> DocxStyle::headingTags() const
{
    return m_headingTags;
}

void DocxStyle::addHeadingStyle()
{

}




}


