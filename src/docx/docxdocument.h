#ifndef DOCXDOCUMENT_H
#define DOCXDOCUMENT_H
#include "docx_global.h"
#include "newdocument.h"


namespace TDocx
{
class DOCX_EXPORT Document
{
public:
    Document();
    Document(const QString &docxName);   

    void writeln();
    void writeln(const QString &text, const RunAlignment alignment = RunAlignment::None);
    void writeln(const QString &text, const DocxFont &font, const RunAlignment alignment = RunAlignment::None);
    void writeHeading(const QString &text, const HeadingLevel headLevel = HeadingLevel::head1, const DocxFont &font = DocxFont());

    void writeList(const DocxListFormat &listStyle, std::initializer_list<QString> outValus);
    void writeList(const DocxListFormat &listStyle, const QString &outStr, std::initializer_list<QString> inValus);

    void insertImage(const QString &imgName, const QSize &size = QSize());

    void insertTable(DocxTable *table);
    void insertSectionFooterAndHeader(std::initializer_list<FootAndHeader *> hfs, bool restarNum = false);

    bool save();
    bool saveAs(const QString &name);
    bool saveAs(QIODevice *device);

    virtual ~Document();

    AbstractDocument * contentDocument() const;

private:
    QString m_docName;    
    AbstractDocument *m_newDoc;

};

}
#endif // DOCXDOCUMENT_H
