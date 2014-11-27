#include "docxdocument.h"
#include <QXmlStreamWriter>
#include <QFile>

namespace TDocx
{

Document::Document()
    : m_docName("New Word.docx")
{
    m_newDoc = new NewDocument();
}

Document::Document(const QString &docxName)   
{
    m_newDoc = new ExistDocument(docxName);
}


void Document::writeln()
{
    m_newDoc->writeln();
}

void Document::writeln(const QString &text, const RunAlignment alignment)
{
    m_newDoc->writeln(text,alignment);
}

void Document::writeln(const QString &text, const DocxFont &font, const RunAlignment alignment)
{
    m_newDoc->writeln(text, font, alignment);
}

void Document::writeHeading(const QString &text, const HeadingLevel headLevel, const DocxFont &font)
{
    m_newDoc->writeHeading(text, headLevel, font);
}




void Document::writeList(const DocxListFormat &listStyle, std::initializer_list<QString> outValus)
{
    m_newDoc->writeList(listStyle, outValus);
}

void Document::writeList(const DocxListFormat &listStyle, const QString &outStr, std::initializer_list<QString> inValus)
{
    m_newDoc->writeList(listStyle, outStr, inValus);
}

void Document::insertImage(const QString &imgName, const QSize &size)
{
    m_newDoc->insertImage(imgName, size);
}

void Document::insertTable(DocxTable *table)
{
    m_newDoc->insertTable(table);
}

void Document::insertSectionFooterAndHeader(std::initializer_list<FootAndHeader *> hfs, bool restarNum)
{
    m_newDoc->insertSectionFooterAndHeader(hfs, restarNum);
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
    m_newDoc->saveAs(device);
    return true;
}

Document::~Document()
{
}

AbstractDocument *Document::contentDocument() const
{
    return m_newDoc;
}

}


