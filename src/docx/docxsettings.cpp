#include "docxsettings.h"
#include "comdatafun.h"
#include <QXmlStreamWriter>

namespace TDocx
{
const QString mc = "http://schemas.openxmlformats.org/markup-compatibility/2006";
const QString o = "urn:schemas-microsoft-com:office:office";
const QString r = "http://schemas.openxmlformats.org/officeDocument/2006/relationships";
const QString m = "http://schemas.openxmlformats.org/officeDocument/2006/math";
const QString v = "urn:schemas-microsoft-com:vml";
const QString w10 = "urn:schemas-microsoft-com:office:word";
const QString w = "http://schemas.openxmlformats.org/wordprocessingml/2006/main";
const QString w14 = "http://schemas.microsoft.com/office/word/2010/wordml";
const QString s1 = "http://schemas.openxmlformats.org/schemaLibrary/2006/main";

DocxSettings::DocxSettings(CreateFlag flag)
    :AbstractOOXmlFile(flag)
{
    if (flag ==  CreateFlag::F_NewFromScratch)
        initTags();
}

DocxSettings::~DocxSettings()
{
    if (m_wTags.count() > 0) {
        for (TagElement* ele : m_wTags) {
            delete ele;
        }
    }
    m_wTags.clear();
}

void DocxSettings::initTags()
{
    TagElement *element = new TagElement(QStringLiteral("w:zoom"));
    element->addProperty(QStringLiteral("w:percent"), QStringLiteral("100"));
    m_wTags.append(element);
    element = new TagElement(QStringLiteral("w:embedSystemFonts"));
    m_wTags.append(element);
    element = new TagElement(QStringLiteral("w:proofState"));
    element->addProperty(QStringLiteral("w:val"), QStringLiteral("clean"));
    m_wTags.append(element);

    element = new TagElement(QStringLiteral("w:stylePaneFormatFilter"));
    element->addProperty(QStringLiteral("w:val"), QStringLiteral("3F01"));
    m_wTags.append(element);

    element = new TagElement(QStringLiteral("w:doNotTrackMoves"));
    m_wTags.append(element);

    element = new TagElement(QStringLiteral("w:defaultTabStop"));
    element->addProperty(QStringLiteral("w:val"), QStringLiteral("720"));
    m_wTags.append(element);

    element = new TagElement(QStringLiteral("w:noPunctuationKerning"));
    m_wTags.append(element);

    element = new TagElement(QStringLiteral("w:characterSpacingControl"));
    element->addProperty(QStringLiteral("w:val"), QStringLiteral("doNotCompress"));
    m_wTags.append(element);

    element = new TagElement(QStringLiteral("w:compat"));
    TagElement *child = new TagElement(QStringLiteral("w:useWord2002TableStyleRules"));
    element->addChild(child);
    child = new TagElement(QStringLiteral("w:growAutofit"));
    element->addChild(child);
    child = new TagElement(QStringLiteral("w:useNormalStyleForList"));
    element->addChild(child);
    child = new TagElement(QStringLiteral("w:doNotUseIndentAsNumberingTabStop"));
    element->addChild(child);
    child = new TagElement(QStringLiteral("w:useAltKinsokuLineBreakRules"));
    element->addChild(child);
    child = new TagElement(QStringLiteral("w:allowSpaceOfSameStyleInTable"));
    element->addChild(child);

    child = new TagElement(QStringLiteral("w:doNotSuppressIndentation"));
    element->addChild(child);
    child = new TagElement(QStringLiteral("w:doNotAutofitConstrainedTables"));
    element->addChild(child);
    child = new TagElement(QStringLiteral("w:autofitToFirstFixedWidthCell"));
    element->addChild(child);
    child = new TagElement(QStringLiteral("w:displayHangulFixedWidth"));
    element->addChild(child);
    child = new TagElement(QStringLiteral("w:splitPgBreakAndParaMark"));
    element->addChild(child);
    child = new TagElement(QStringLiteral("w:doNotVertAlignCellWithSp"));
    element->addChild(child);
    child = new TagElement(QStringLiteral("w:doNotBreakConstrainedForcedTable"));
    element->addChild(child);
    child = new TagElement(QStringLiteral("w:doNotVertAlignInTxbx"));
    element->addChild(child);
    child = new TagElement(QStringLiteral("w:useAnsiKerningPairs"));
    element->addChild(child);
    child = new TagElement(QStringLiteral("w:cachedColBalance"));
    element->addChild(child);


    m_wTags.append(element);

    // mathPr
    element = new TagElement(QStringLiteral("m:mathPr"));
    child = new TagElement(QStringLiteral("m:mathFont"));
    child->addProperty(QStringLiteral("m:val"), QStringLiteral("Cambria Math"));
    element->addChild(child);
    child = new TagElement(QStringLiteral("m:brkBin"));
    child->addProperty(QStringLiteral("m:val"), QStringLiteral("before"));
    element->addChild(child);

    child = new TagElement(QStringLiteral("m:brkBinSub"));
    child->addProperty(QStringLiteral("m:val"), QStringLiteral("--"));

    element->addChild(child);
    child = new TagElement(QStringLiteral("m:smallFrac"));
    child->addProperty(QStringLiteral("m:val"), QStringLiteral("0"));
    element->addChild(child);

    child = new TagElement(QStringLiteral("m:dispDef"));
    element->addChild(child);

    child = new TagElement(QStringLiteral("m:lMargin"));
    child->addProperty(QStringLiteral("m:val"), QStringLiteral("0"));
    element->addChild(child);

    child = new TagElement(QStringLiteral("m:rMargin"));
    child->addProperty(QStringLiteral("m:val"), QStringLiteral("0"));
    element->addChild(child);

    child = new TagElement(QStringLiteral("m:defJc"));
    child->addProperty(QStringLiteral("m:val"), QStringLiteral("centerGroup"));
    element->addChild(child);

    child = new TagElement(QStringLiteral("m:wrapIndent"));
    child->addProperty(QStringLiteral("m:val"), QStringLiteral("1440"));
    element->addChild(child);

    child = new TagElement(QStringLiteral("m:intLim"));
    child->addProperty(QStringLiteral("m:val"), QStringLiteral("subSup"));
    element->addChild(child);

    child = new TagElement(QStringLiteral("m:naryLim"));
    child->addProperty(QStringLiteral("m:val"), QStringLiteral("undOvr"));
    element->addChild(child);

    m_wTags.append(element);
    // end mathPr

    // themeFontLang
    element = new TagElement(QStringLiteral("w:themeFontLang"));
    element->addProperty(QStringLiteral("w:val"), QStringLiteral("en-US"));
    element->addProperty(QStringLiteral("w:eastAsia"), QStringLiteral("zh-CN"));
    m_wTags.append(element);


    // clrSchemeMapping
    element = new TagElement(QStringLiteral("w:clrSchemeMapping"));
    element->addProperty(QStringLiteral("w:bg1"), QStringLiteral("light1"));
    element->addProperty(QStringLiteral("w:t1"), QStringLiteral("dark1"));
    element->addProperty(QStringLiteral("w:bg2"), QStringLiteral("light2"));
    element->addProperty(QStringLiteral("w:t2"), QStringLiteral("dark2"));
    element->addProperty(QStringLiteral("w:accent1"), QStringLiteral("accent1"));
    element->addProperty(QStringLiteral("w:accent2"), QStringLiteral("accent2"));
    element->addProperty(QStringLiteral("w:accent3"), QStringLiteral("accent3"));
    element->addProperty(QStringLiteral("w:accent4"), QStringLiteral("accent4"));
    element->addProperty(QStringLiteral("w:accent5"), QStringLiteral("accent5"));
    element->addProperty(QStringLiteral("w:accent6"), QStringLiteral("accent6"));
    element->addProperty(QStringLiteral("w:hyperlink"), QStringLiteral("hyperlink"));
    element->addProperty(QStringLiteral("w:followedHyperlink"), QStringLiteral("followedHyperlink"));
    m_wTags.append(element);

    // shapeDefaults
    element = new TagElement(QStringLiteral("w:shapeDefaults"));
    child = new TagElement(QStringLiteral("o:shapedefaults"));
    child->addProperty(QStringLiteral("v:ext"), QStringLiteral("edit"));
    child->addProperty(QStringLiteral("spidmax"), QStringLiteral("1026"));
    element->addChild(child);

    child = new TagElement(QStringLiteral("o:shapelayout"));
    child->addProperty(QStringLiteral("v:ext"), QStringLiteral("edit"));
    TagElement * secondLevelChild = new TagElement(QStringLiteral("o:idmap"));
    secondLevelChild->addProperty(QStringLiteral("v:ext"), QStringLiteral("edit"));
    secondLevelChild->addProperty(QStringLiteral("data"), QStringLiteral("1"));
    child->addChild(secondLevelChild);

    element->addChild(child);
    m_wTags.append(element);

    // decimalSymbol
    element = new TagElement(QStringLiteral("w:decimalSymbol"));
    element->addProperty(QStringLiteral("w:val"), QStringLiteral("."));
    m_wTags.append(element);

    // listSeparator
    element = new TagElement(QStringLiteral("w:listSeparator"));
    element->addProperty(QStringLiteral("w:val"), QStringLiteral(","));
    m_wTags.append(element);
}




void DocxSettings::saveToXmlFile(QIODevice *device) const
{
    QXmlStreamWriter writer(device);
    writer.writeStartDocument(QStringLiteral("1.0"), true);
    writer.writeStartElement(QStringLiteral("w:settings"));
    writer.writeNamespace(mc, QStringLiteral("mc"));
    writer.writeNamespace(o, QStringLiteral("o"));
    writer.writeNamespace(r, QStringLiteral("r"));
    writer.writeNamespace(m, QStringLiteral("m"));
    writer.writeNamespace(v, QStringLiteral("v"));
    writer.writeNamespace(w10, QStringLiteral("w10"));
    writer.writeNamespace(w, QStringLiteral("w"));
    writer.writeNamespace(w14, QStringLiteral("w14"));
    writer.writeNamespace(s1, QStringLiteral("s1"));
    writer.writeAttribute(mc, QStringLiteral("Ignorable"), QStringLiteral("w14"));
    for (const TagElement* element : m_wTags) {
        element->saveToXmlElement(&writer);
    }
    writer.writeEndElement(); // end w:settings
    writer.writeEndDocument();
}

bool DocxSettings::loadFromXmlFile(QIODevice *device)
{
    return true;
}

}



