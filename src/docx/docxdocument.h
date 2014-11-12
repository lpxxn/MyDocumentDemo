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

#include <QString>
#include <QMap>

#include <initializer_list>

namespace TDocx
{

class DOCX_EXPORT Document : public AbstractOOXmlFile
{
public:
    Document();
    Document(CreateFlag flag);

    void writeln(const QString &text);
    void writeln(const QString &text, const DocxFont &font);
    void writeHeading(const QString &text, const HeadingLevel headLevel = HeadingLevel::head1, const DocxFont &font = DocxFont());


    void writeList(const DocxListFormat &listStyle, std::initializer_list<QString> outValus);
    void writeList(const DocxListFormat &listStyle, const QString &outStr, std::initializer_list<QString> inValus);

    DocxParagraph *currentParagraph();
    void addParagraph();
    DocxFont& font();
    void setFont(const DocxFont &font);

    bool save() const;
    bool saveAs(const QString &name) const;
    bool saveAs(QIODevice *device) const;

private:
    void writeList(const DocxListFormat &listStyle, const QString &outStr, bool isindent = false);
    void saveToXmlFile(QIODevice *device) const;
    bool loadFromXmlFile(QIODevice *device);

private:
    QVector<DocxParagraph*> m_paragraphs;
    QString m_docName;
    DocxFont m_font;

    ContentTypes m_contentTypes;
    DocPropsApp m_docPropsApp;
    DocPropsCore m_docPropsCore;
    DocxTheme m_docxTheme;
    DocxfontTable m_docxfontTable;
    DocxSettings m_docxSettings;
    DocxWebSetting m_docxWebSetting;
    DocxStyle m_docxStyle;
    DocxNumbering m_numbering;
    QMap<QString, QString> m_docrels;

    friend class DocumentBuilder;    

};
}
#endif // DOCXDOCUMENT_H
