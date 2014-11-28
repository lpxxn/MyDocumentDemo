#ifndef DOCXXMLREADER_H
#define DOCXXMLREADER_H
#include "docx_global.h"
#include "docxparagraph.h"

#include <QXmlStreamReader>


namespace TDocx
{
class DOCX_EXPORT DocxXmlReader
{
public:
    DocxXmlReader(QIODevice *device);
    void readStartElement();
    void readStartElement(DocxParagraph * parent);

private:
    QList<DocxParagraph *> m_paragraphs;
    QXmlStreamReader m_xmlReader;
};
}

#endif // DOCXXMLREADER_H
