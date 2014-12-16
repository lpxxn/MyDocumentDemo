#ifndef DOCXDOCUMENT_H
#define DOCXDOCUMENT_H
#include "docx_global.h"
#include "abstractooxmlfile.h"
#include "docxdocumentbuilder.h"
#include "docxparagraph.h"
#include "docxfont.h"
#include "relationships.h"
#include "contenttypes.h"
#include "docpropsapp.h"
#include "docpropscore.h"
#include "docxtheme.h"
#include "docxfonttable.h"
#include "docxsettings.h"
#include "docxwebsetting.h"
#include "docxstyle.h"
#include "docxstyleheading.h"
#include "docxlistformat.h"
#include "docxnumbering.h"
#include "docxmediafile.h"
#include "footandheader.h"
#include "mergetable.h"
#include "docxxmlreader.h"
#include "docxzipreader.h"

#include <QString>
#include <QMap>
#include <QQueue>

#include <initializer_list>

namespace TDocx
{
class DocxTable;

class AbstractDocument : public AbstractOOXmlFile
{
public:
    AbstractDocument(CreateFlag flag);
    bool saveAs(const QString &name);
    virtual bool saveAs(QIODevice *device) = 0;
    virtual void saveToXmlFile(QIODevice *device) const = 0;
    virtual bool loadFromXmlFile(QIODevice *device) = 0;

protected:
    DocxStyle m_docxStyle;
    ContentTypes m_contentTypes;
    Relationships m_documentShips;

protected:
    DocxInsertImagePrivate *m_inserImagePrivate;
    bool m_haveImg = false;
    friend class DocxInsertImagePrivate;
    friend class DocxTable;
    friend class FootAndHeader;

};

class DOCX_EXPORT Document : public AbstractDocument
{
public:
    Document();    
    void saveToXmlFile(QIODevice *device) const;
    bool loadFromXmlFile(QIODevice *device);

    void addParagraph();
    DocxParagraph *lastParagraph();
    // write element

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

private:
    void writeList(const DocxListFormat &listStyle, const QString &outStr, bool isindent = false);
    void iniElement();
    TagElement *HeaderOrFooterElement(FootAndHeader *hf);
    TagElement *initDocumentEndElement() const;

private:
    DocxWebSetting m_docxWebSetting;
    DocxNumbering m_numbering;
    DocxSettings m_docxSettings;
    DocPropsApp m_docPropsApp;
    DocPropsCore m_docPropsCore;
    DocxTheme m_docxTheme;
    DocxfontTable m_docxfontTable;

    QString m_docName;

private:
    QVector<DocxParagraph*> m_paragraphs;
    QVector<FootAndHeader*> m_headers;
    Relationships m_wordShips;
    QQueue<TagElement *> m_endElements;

};


class DOCX_EXPORT ExistDocument : public AbstractDocument
{
public:
    ExistDocument(const QString &docxName);
    void saveToXmlFile(QIODevice *device) const;
    bool loadFromXmlFile(QIODevice *device);

    bool saveAs(const QString &name);
    bool saveAs(QIODevice *device);

    void merge();
    void addSignalMergeElement(const QString &name, const QString &value);
    void addMergeTable(MergeTable *table);

private:
    // m_zipReader;
    DocxXmlReader *m_xmlReader;
    QMap<QString, QByteArray> m_otherFiles;
};

}
#endif // DOCXDOCUMENT_H
