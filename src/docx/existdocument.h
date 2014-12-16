#ifndef EXISTDOCUMENT_H
#define EXISTDOCUMENT_H
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

/*!
 * \brief Load a Exist Document
 */
class DOCX_EXPORT ExistDocument : public AbstractOOXmlFile
{
public:
    ExistDocument(const QString &docxName);
    void saveToXmlFile(QIODevice *device) const;
    bool loadFromXmlFile(QIODevice *device);

    bool saveAs(const QString &name);
    bool saveAs(QIODevice *device);

    void writeln();
    void writeln(const QString &text, const RunAlignment alignment = RunAlignment::None);
    void writeln(const QString &text, const DocxFont &font, const RunAlignment alignment = RunAlignment::None);
    void writeHeading(const QString &text, const HeadingLevel headLevel = HeadingLevel::head1, const DocxFont &font = DocxFont());

    void writeList(const DocxListFormat &listStyle, std::initializer_list<QString> outValus);
    void writeList(const DocxListFormat &listStyle, const QString &outStr, std::initializer_list<QString> inValus);

    void insertImage(const QString &imgName, const QSize &size = QSize());

    void insertTable(DocxTable *table);
    void insertSectionFooterAndHeader(std::initializer_list<FootAndHeader *> hfs, bool restarNum = false);

    void merge();
    void addSignalMergeElement(const QString &name, const QString &value);
    void addMergeTable(MergeTable *table);

private:    
    // m_zipReader;
    DocxXmlReader *m_xmlReader;
    QMap<QString, QByteArray> m_otherFiles;
};

}

#endif // NEWDOCUMENT_H
