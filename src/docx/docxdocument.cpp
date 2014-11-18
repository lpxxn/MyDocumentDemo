#include "docxdocument.h"
#include "docxzipwriter.h"
#include "docxtable.h"

#include <QXmlStreamWriter>
#include <QFile>

namespace TDocx
{
const QString wpc = QStringLiteral("http://schemas.microsoft.com/office/word/2010/wordprocessingCanvas");
const QString mc = QStringLiteral("http://schemas.openxmlformats.org/markup-compatibility/2006");
const QString o = QStringLiteral("urn:schemas-microsoft-com:office:office");
const QString r = QStringLiteral("http://schemas.openxmlformats.org/officeDocument/2006/relationships");
const QString m = QStringLiteral("http://schemas.openxmlformats.org/officeDocument/2006/math");
const QString v = QStringLiteral("urn:schemas-microsoft-com:vml");
const QString wp14 = QStringLiteral("http://schemas.microsoft.com/office/word/2010/wordprocessingDrawing");
const QString wp = QStringLiteral("http://schemas.openxmlformats.org/drawingml/2006/wordprocessingDrawing");
const QString w10 = QStringLiteral("urn:schemas-microsoft-com:office:word");
const QString w = QStringLiteral("http://schemas.openxmlformats.org/wordprocessingml/2006/main");
const QString w14 = QStringLiteral("http://schemas.microsoft.com/office/word/2010/wordml");
const QString wpg = QStringLiteral("http://schemas.microsoft.com/office/word/2010/wordprocessingGroup");
const QString wpi = QStringLiteral("http://schemas.microsoft.com/office/word/2010/wordprocessingInk");
const QString wne = QStringLiteral("http://schemas.microsoft.com/office/word/2006/wordml");
const QString wps = QStringLiteral("http://schemas.microsoft.com/office/word/2010/wordprocessingShape");
const QString strEndpr = R"~(
        <w:sectPr>
        <w:pgSz w:w="12240" w:h="15840"/>
        <w:pgMar w:top="1440" w:right="1800" w:bottom="1440" w:left="1800" w:header="708" w:footer="708" w:gutter="0"/>
        <w:cols w:space="708"/>
        <w:docGrid w:linePitch="360"/>
        </w:sectPr>
        )~";


Document::Document()
    : Document(CreateFlag::F_NewFromScratch)
{

}

Document::Document(CreateFlag flag)
    : AbstractOOXmlFile(flag), m_docName(QStringLiteral("word.docx")), m_numbering(flag),
      m_contentTypes(flag), m_docPropsApp(flag), m_docPropsCore(flag), m_docxTheme(flag),
      m_docxfontTable(flag), m_docxSettings(flag), m_docxWebSetting(flag), m_docxStyle(flag)
{
    m_inserImagePrivate = new DocxInsertImagePrivate(this);
    if (flag == CreateFlag::F_NewFromScratch)
        addParagraph();
}

void Document::writeln()
{
    addParagraph();
}

void Document::writeln(const QString &text)
{
    DocxParagraph* current = lastParagraph();
    current->setText(text);
    addParagraph();
}

void Document::writeln(const QString &text, const DocxFont &font)
{
    DocxParagraph* current = lastParagraph();
    current->setFont(font);
    current->setText(text);
    addParagraph();
}

void Document::writeHeading(const QString &text, const HeadingLevel headLevel, const DocxFont &font)
{
    DocxParagraph* current = lastParagraph();
    AbsHeading *head;
    head = m_docxStyle.headbyLevel(headLevel);
    if (!head) {
        head = HeadingFactory::heading(headLevel);
        m_docxStyle.addHeadingStyle(head);
    }

    TagElement *styleElement = new TagElement(QStringLiteral("w:pStyle"));
    styleElement->addProperty(QStringLiteral("w:val"), head->headId());
    current->addStyleProperty(styleElement);
    current->setFont(font);
    current->setText(text);
    addParagraph();
}


/*!
 * \brief 添加列表
 * \param listStyle
 * \param outValus
 */
void Document::writeList(const DocxListFormat &listStyle, const QString &outStr, bool isindent)
{
    DocxParagraph* current = lastParagraph();
    //DocxListFormat docx(listStyle);
    TagElement *styleElement = new TagElement(QStringLiteral("w:numPr"));
    TagElement *child = new TagElement(QStringLiteral("w:ilvl"));
    child->addProperty(QStringLiteral("w:val"), isindent ? QStringLiteral("1") : QStringLiteral("0"));
    styleElement->addChild(child);

    child = new TagElement(QStringLiteral("w:numId"));
    child->addProperty(QStringLiteral("w:val"), QString::number((int)listStyle.flag()));
    styleElement->addChild(child);

    current->addStyleProperty(styleElement);
    current->setFont(listStyle.font());
    current->setText(outStr);
    addParagraph();
}


void Document::writeList(const DocxListFormat &listStyle, std::initializer_list<QString> outValus)
{
    for (const QString &str : outValus) {
        writeList(listStyle, str);
    }
}

void Document::writeList(const DocxListFormat &listStyle, const QString &outStr, std::initializer_list<QString> inValus)
{
    writeList(listStyle, outStr);
    for (const QString &str : inValus) {
        writeList(listStyle, str, true);
    }
}




void Document::insertImage(const QString &imgName, const QSize &size)
{
    DocxParagraph* current = lastParagraph();
    TagElement *shap = m_inserImagePrivate->imageTagElement(imgName, size);
    current->addContentElement(shap);
    addParagraph();
}

void Document::insertTable(DocxTable *table)
{
    m_paragraphs.append(table);
    addParagraph();
}

void Document::saveToXmlFile(QIODevice *device) const
{
    QXmlStreamWriter writer(device);
    writer.writeStartDocument(QStringLiteral("1.0"), true);
    writer.writeStartElement("w:document");
    writer.writeNamespace(wpc, QStringLiteral("wpc"));
    writer.writeNamespace(mc, QStringLiteral("mc"));
    writer.writeNamespace(o, QStringLiteral("o"));
    writer.writeNamespace(r, QStringLiteral("r"));
    writer.writeNamespace(m, QStringLiteral("m"));
    writer.writeNamespace(v, QStringLiteral("v"));
    writer.writeNamespace(wp14, QStringLiteral("wp14"));
    writer.writeNamespace(wp, QStringLiteral("wp"));
    writer.writeNamespace(w10, QStringLiteral("w10"));
    writer.writeNamespace(w, QStringLiteral("w"));
    writer.writeNamespace(w14, QStringLiteral("w14"));
    writer.writeNamespace(wpg, QStringLiteral("wpg"));
    writer.writeNamespace(wpi, QStringLiteral("wpi"));
    writer.writeNamespace(wne, QStringLiteral("wne"));
    writer.writeNamespace(wps, QStringLiteral("wps"));
    writer.writeAttribute(mc, QStringLiteral("Ignorable"), QStringLiteral("w14 wp14"));
    writer.writeStartElement(QStringLiteral("w:body"));
    writer.writeComment(QStringLiteral("body"));

    for (const DocxParagraph *p : m_paragraphs) {
        p->saveToXmlElement(&writer);
    }

    writer.writeComment(QStringLiteral("end"));
    device->write(strEndpr.toUtf8());
    writer.writeEndElement();// end body

    writer.writeEndElement(); // end w:document
    writer.writeEndDocument();
}

bool Document::loadFromXmlFile(QIODevice *device)
{
    return true;
}

DocxFont &Document::font()
{
    return m_font;
}

void Document::setFont(const DocxFont &font)
{
    m_font = font;
}

bool Document::save()
{
    return saveAs(m_docName);
}

bool Document::saveAs(const QString &name)
{
    QFile file(name);
    if (file.open(QIODevice::WriteOnly))
        return saveAs(&file);
    return false;
}

bool Document::saveAs(QIODevice *device)
{
    DocxZipWriter writer(device);
    // _rels/.rels

    m_wordShips.addDocumentRelationship(QStringLiteral("/officeDocument"), QStringLiteral("word/document.xml"));
    m_wordShips.addDocumentRelationship(QStringLiteral("/extended-properties"), QStringLiteral("docProps/app.xml"));
    m_wordShips.addPackageRelationship(QStringLiteral("/metadata/core-properties"), QStringLiteral("docProps/core.xml"));
    writer.addFile(QStringLiteral("_rels/.rels"), m_wordShips.saveToXmlData());

    // [Content_Types].xml
    writer.addFile(QStringLiteral("[Content_Types].xml"), m_contentTypes.saveToXmlData());

    // docProps/app.xml
    writer.addFile(QStringLiteral("docProps/app.xml"), m_docPropsApp.saveToXmlData());

    // docProps/core.xml
    writer.addFile(QStringLiteral("docProps/core.xml"), m_docPropsCore.saveToXmlData());

    // word/theme/theme1.xml
    writer.addFile(QStringLiteral("word/theme/theme1.xml"), m_docxTheme.saveToXmlData());

    // word/_rels/document.xml.rels
    m_documentShips.addDocumentRelationship(QStringLiteral("/settings"), QStringLiteral("settings.xml"));
    m_documentShips.addDocumentRelationship(QStringLiteral("/styles"), QStringLiteral("styles.xml"));
    m_documentShips.addDocumentRelationship(QStringLiteral("/theme"), QStringLiteral("theme/theme1.xml"));
    m_documentShips.addDocumentRelationship(QStringLiteral("/fontTable"), QStringLiteral("fontTable.xml"));
    m_documentShips.addDocumentRelationship(QStringLiteral("/webSettings"), QStringLiteral("webSettings.xml"));
    m_documentShips.addDocumentRelationship(QStringLiteral("/numbering"), QStringLiteral("numbering.xml"));
    QMapIterator<QString, QString> iter(m_docrels);
    while (iter.hasNext()) {
        m_documentShips.addDocumentRelationship(iter.key(), iter.value());
    }
    writer.addFile(QStringLiteral("word/_rels/document.xml.rels"), m_documentShips.saveToXmlData());

    //word/fontTable.xml
    writer.addFile(QStringLiteral("word/fontTable.xml"), m_docxfontTable.saveToXmlData());

    // word/settings.xml
    writer.addFile(QStringLiteral("word/settings.xml"), m_docxSettings.saveToXmlData());

    // word/webSettings.xml
    writer.addFile(QStringLiteral("word/webSettings.xml"), m_docxWebSetting.saveToXmlData());

    // word/styles.xml
    writer.addFile(QStringLiteral("word/styles.xml"), m_docxStyle.saveToXmlData());

    // word/numbering.xml
    writer.addFile(QStringLiteral("word/numbering.xml"), m_numbering.saveToXmlData());

    // word/document.xml
    writer.addFile(QStringLiteral("word/document.xml"), this->saveToXmlData());

    // media/image
    for (const DocxMediaFile *img : m_inserImagePrivate->imgs()) {
        writer.addFile(QString("word/media/%1").arg(img->name()), img->content());
    }

    writer.close();
    return true;
}

Document::~Document()
{
    delete m_inserImagePrivate;
}

DocxParagraph *Document::lastParagraph()
{
    return m_paragraphs.last();
}

void Document::addParagraph()
{
    m_paragraphs.append(new DocxParagraph());
}

}


