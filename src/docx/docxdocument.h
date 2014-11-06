#ifndef DOCXDOCUMENT_H
#define DOCXDOCUMENT_H
#include "docx_global.h"
#include "abstractooxmlfile.h"
#include "docxdocumentbuilder.h"
#include "docxparagraph.h"
#include "docxfont.h"

#include <QString>

namespace TDocx
{
class DOCX_EXPORT Document : public AbstractOOXmlFile
{
public:
    Document(CreateFlag flag);

    void writeln(const QString &text);
    void writeln(const QString &text, const DocxFont &font);

    DocxParagraph *currentParagraph();
    void addParagraph();
    DocxFont& font();
    void setFont(const DocxFont &font);

private:
    void saveToXmlFile(QIODevice *device) const;
    bool loadFromXmlFile(QIODevice *device);

private:
    QVector<DocxParagraph*> m_paragraphs;
    DocxFont m_font;
    friend class DocumentBuilder;    

};
}
#endif // DOCXDOCUMENT_H
