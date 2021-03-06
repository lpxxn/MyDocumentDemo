#include "docxdocument.h"
#include "docxzipwriter.h"
#include "docxtable.h"

#include <QXmlStreamWriter>
#include <QFile>
#include <QBuffer>
#include <QDebug>

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


AbstractDocument::AbstractDocument(AbstractOOXmlFile::CreateFlag flag)
    : AbstractOOXmlFile(flag), m_contentTypes(flag), m_docxStyle(flag)
{
    m_inserImagePrivate = new DocxInsertImagePrivate(this);
}

bool AbstractDocument::saveAs(const QString &name)
{
    QFile file(name);
    if (file.open(QIODevice::WriteOnly))
        return saveAs(&file);
    return false;
}

void AbstractDocument::loadDocxRelaction(const QByteArray &data)
{
    QBuffer buffer;
    buffer.setData(data);
    buffer.open(QIODevice::ReadOnly);

    QXmlStreamReader reader(&buffer);
    while (!reader.atEnd()) {
        reader.readNextStartElement();

        if (reader.name() == QLatin1String("Relationship")) {
            QXmlStreamAttributes attrs = reader.attributes();
            QString id =  attrs.value(QLatin1String("Id")).toString();
            if (id.isEmpty())
                continue;
            QString type = attrs.value(QLatin1String("Type")).toString();
            QString target = attrs.value(QLatin1String("Target")).toString();
            m_documentShips.addLoadRelationship(id, type, target);
        }

        if (reader.hasError()) {
            qDebug() << QStringLiteral("Document RelactionShip read error :") << reader.errorString();
        }
    }
}

TagElement * AbstractDocument::imgElement(const QString &imgName, const QSize &size)
{
    TagElement *shap = m_inserImagePrivate->imageTagElement(imgName, size, !m_haveImg);
    m_haveImg = true;

    return shap;
}

// end AbstractDocument

Document::Document()
    : AbstractDocument(CreateFlag::F_NewFromScratch), m_numbering(CreateFlag::F_NewFromScratch)
    , m_docxWebSetting(CreateFlag::F_NewFromScratch), m_docxSettings(CreateFlag::F_NewFromScratch), m_docPropsApp(CreateFlag::F_NewFromScratch), m_docPropsCore(CreateFlag::F_NewFromScratch)
    , m_docxTheme(CreateFlag::F_NewFromScratch), m_docxfontTable(CreateFlag::F_NewFromScratch)
    , m_docName("New Word.docx")
{
    iniElement();
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
    //device->write(strEndpr.toUtf8());
    //m_DocEndElement->saveToXmlElement(&writer);
    if (!m_endElements.isEmpty()) {
        TagElement *ele = m_endElements.back();
        ele->saveToXmlElement(&writer);
    } else {
        TagElement *ele = initDocumentEndElement();
        ele->saveToXmlElement(&writer);
    }
    writer.writeEndElement();// end body

    writer.writeEndElement(); // end w:document
    writer.writeEndDocument();
}

bool Document::loadFromXmlFile(QIODevice *device)
{
    return true;
}

void Document::addParagraph()
{
    m_paragraphs.append(new DocxParagraph());
}

DocxParagraph *Document::lastParagraph()
{
    return m_paragraphs.last();
}


void Document::writeln()
{
    addParagraph();
}

void Document::writeln(const QString &text, const RunAlignment alignment)
{
    DocxParagraph* current = lastParagraph();
    current->addTextChild(text);
    current->setAlignment(alignment);
    addParagraph();
}

void Document::writeln(const QString &text, const DocxFont &font, const RunAlignment alignment)
{
    DocxParagraph* current = lastParagraph();
    current->addTextChild(text, font);
    current->setAlignment(alignment);
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
    current->addTextChild(text, font);
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
    TagElement *shap = imgElement(imgName, size);
    current->addChild(shap);
    addParagraph();
}

void Document::insertTable(DocxTable *table)
{
    m_paragraphs.append(table);
    addParagraph();
}

void Document::insertSectionFooterAndHeader(std::initializer_list<FootAndHeader *> hfs, bool restarNum)
{
    TagElement *endElement = initDocumentEndElement();
    for (FootAndHeader * hf : hfs) {
        TagElement *ele = HeaderOrFooterElement(hf);
        endElement->addChild(ele);
    }

    if (restarNum) {
        TagElement *num = new TagElement("w:pgNumType");
        num->addProperty(QStringLiteral("w:start"), QStringLiteral("1"));
        endElement->addChild(num);
    }
    m_endElements.append(endElement);
    if (m_endElements.size() > 1) {
        addParagraph();
        DocxParagraph* current = lastParagraph();
        current->addStyleProperty(m_endElements.dequeue());
        addParagraph();
    }
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

    // word/header and footer
    for (const FootAndHeader *h : m_headers) {
        writer.addFile(QStringLiteral("word/") + h->name(), h->saveToXmlData());
        if (!h->relationships()->isEmpty())
            writer.addFile(QString("word/_rels/%1.rels").arg(h->name()) ,h->relationships()->saveToXmlData());
    }

    // word/document.xml
    writer.addFile(QStringLiteral("word/document.xml"), this->saveToXmlData());

    // media/image
    for (const DocxMediaFile *img : m_inserImagePrivate->imgs()) {
        writer.addFile(QString("word/media/%1").arg(img->name()), img->content());
    }

    writer.close();
    return true;
}

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
    current->addTextChild(outStr, listStyle.font());
    addParagraph();
}

void Document::iniElement()
{
    // _rels/.rels
    m_wordShips.addDocumentRelationship(QStringLiteral("/officeDocument"), QStringLiteral("word/document.xml"));
    m_wordShips.addDocumentRelationship(QStringLiteral("/extended-properties"), QStringLiteral("docProps/app.xml"));
    m_wordShips.addPackageRelationship(QStringLiteral("/metadata/core-properties"), QStringLiteral("docProps/core.xml"));

    // word/_rels/document.xml.rels
    m_documentShips.addDocumentRelationship(QStringLiteral("/settings"), QStringLiteral("settings.xml"));
    m_documentShips.addDocumentRelationship(QStringLiteral("/styles"), QStringLiteral("styles.xml"));
    m_documentShips.addDocumentRelationship(QStringLiteral("/theme"), QStringLiteral("theme/theme1.xml"));
    m_documentShips.addDocumentRelationship(QStringLiteral("/fontTable"), QStringLiteral("fontTable.xml"));
    m_documentShips.addDocumentRelationship(QStringLiteral("/webSettings"), QStringLiteral("webSettings.xml"));
    m_documentShips.addDocumentRelationship(QStringLiteral("/numbering"), QStringLiteral("numbering.xml"));
}

TagElement *Document::HeaderOrFooterElement(FootAndHeader *hf)
{
    QString name = hf->prefix() + QString::number(m_headers.count() + 1) + QStringLiteral(".xml");
    hf->setName(name);
    // contentTypes
    m_contentTypes.addDocumentOverride(QStringLiteral("/word/") + hf->name(), QStringLiteral(".wordprocessingml.") + hf->prefix()+ QStringLiteral("+xml"));
    QString headerId;

    // word/_rels/document.xml.rels
    m_documentShips.addDocumentRelationship(QStringLiteral("/") + hf->prefix(), hf->name(), headerId);
    hf->setId(headerId);

    TagElement *child = new TagElement(hf->reference());
    child->addProperty(QStringLiteral("w:type"), hf->type());
    child->addProperty(QStringLiteral("r:id"), hf->id());
    m_headers.append(hf);

    return child;
}

TagElement *Document::initDocumentEndElement() const
{
    TagElement *docEndElement = new TagElement(QStringLiteral("w:sectPr"));
    TagElement *child = new TagElement(QStringLiteral("w:pgSz"));
    child->addProperty(QStringLiteral("w:w"), QStringLiteral("12240"));
    child->addProperty(QStringLiteral("w:h"), QStringLiteral("15840"));
    docEndElement->addChild(child);

    child = new TagElement(QStringLiteral("w:pgMar"));
    child->addProperty(QStringLiteral("w:top"), QStringLiteral("1440"));
    child->addProperty(QStringLiteral("w:right"), QStringLiteral("1800"));
    child->addProperty(QStringLiteral("w:bottom"), QStringLiteral("1440"));
    child->addProperty(QStringLiteral("w:left"), QStringLiteral("1800"));
    child->addProperty(QStringLiteral("w:header"), QStringLiteral("708"));
    child->addProperty(QStringLiteral("w:footer"), QStringLiteral("708"));
    child->addProperty(QStringLiteral("w:gutter"), QStringLiteral("0"));
    docEndElement->addChild(child);

    child = new TagElement(QStringLiteral("w:cols"));
    child->addProperty(QStringLiteral("w:space"), QStringLiteral("708"));
    docEndElement->addChild(child);

    child = new TagElement(QStringLiteral("w:docGrid"));
    child->addProperty(QStringLiteral("w:linePitch"), QStringLiteral("360"));
    docEndElement->addChild(child);
    return docEndElement;
}

Document::~Document()
{
}

// exist Document

int imgCount = 0;

ExistDocument::ExistDocument(const QString &docxName)
    : AbstractDocument(CreateFlag::F_LoadFromExists)
{
    if (QFile::exists(docxName)) {
        QFile file(docxName);
        if (file.open(QFile::ReadOnly))
            loadFromXmlFile(&file);
    }
}

void ExistDocument::saveToXmlFile(QIODevice *device) const
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

    m_xmlReader->saveElement(&writer);

    writer.writeComment(QStringLiteral("end"));

    writer.writeEndElement();// end body

    writer.writeEndElement(); // end w:document
    writer.writeEndDocument();
}

bool ExistDocument::loadFromXmlFile(QIODevice *device)
{
    DocxZipReader zipReader(device);
    QStringList filePaths = zipReader.filePaths();

    int mediaImgCount = 0;
    //Load Content_Types file
    if (!filePaths.contains(QLatin1String("[Content_Types].xml")))
        return false;
    for (const QString &fpath : filePaths) {
        if (fpath == QStringLiteral("[Content_Types].xml")) {
            m_contentTypes.loadFromXmlData(zipReader.fileData(QStringLiteral("[Content_Types].xml")));
        } else if (fpath == QString("word/_rels/document.xml.rels")) {
            loadDocxRelaction(zipReader.fileData(QStringLiteral("word/_rels/document.xml.rels")));
        } else if (fpath == QString("word/document.xml")) {

            QByteArray data = zipReader.fileData(fpath);

            m_xmlReader = new DocxXmlReader(data, this);

        } else {
            if (fpath.contains(QStringLiteral("word/media/image"), Qt::CaseInsensitive))
                ++mediaImgCount;
            QByteArray data = zipReader.fileData(fpath);
            m_otherFiles.insert(fpath, data);
        }
    }
    if (mediaImgCount > 0)
        m_inserImagePrivate->setLoadImgCount(mediaImgCount);

    return true;
}

bool ExistDocument::saveAs(const QString &name)
{
    QFile file(name);
    if (file.open(QIODevice::WriteOnly))
        return this->saveAs(&file);
    return false;
}

bool ExistDocument::saveAs(QIODevice *device)
{
    DocxZipWriter writer(device);

    QMapIterator<QString, QByteArray> iter(m_otherFiles);
    while (iter.hasNext()) {
        iter.next();
        writer.addFile(iter.key(), iter.value());
    }
    // word/document.xml
    writer.addFile(QStringLiteral("word/document.xml"), this->saveToXmlData());
    // [Content_Types].xml
    writer.addFile(QStringLiteral("[Content_Types].xml"), m_contentTypes.saveToXmlData());

    // word/_rels/document.xml.rels
    writer.addFile(QStringLiteral("word/_rels/document.xml.rels"), m_documentShips.saveToXmlData());

    // media/image
    for (const DocxMediaFile *img : m_inserImagePrivate->imgs()) {
        writer.addFile(QString("word/media/%1").arg(img->name()), img->content());
    }

    writer.close();
    return true;
}

void ExistDocument::merge()
{
    m_xmlReader->readStartElement();
}

void ExistDocument::addSignalMergeElement(const QString &name, const QString &value)
{
    m_xmlReader->addSignalMergeElement(name, value);
}

void ExistDocument::addMergeImg(const QString &imgName, const QString &imgPath, const QSize &size)
{
    m_xmlReader->addMergeImg(imgName, imgPath, size);
}

void ExistDocument::addMergeTable(MergeTable *table)
{
    m_xmlReader->addMergeTable(table);
}

}


