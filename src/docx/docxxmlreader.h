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

    void readPMark(DocxParagraph *parent);
    //void readRunMark(ITagElement *parent);
    void readCommonMark(ITagElement *parent);
    //void readTMark(TagElement *parent);

    //void readCharactersMark(ITagElement *parent);
    QString elementName() const;
    QByteArray saveToXmlData();
    void saveElement(QXmlStreamWriter *writer);

    bool isEndElement(const QString &markName);

private:
    void addMarketAtributes(DocxParagraph *para);
    void addMarketAtributes(TagElement *element);
    bool readNextMark();
    void checkSkipMark();

private:
    QList<DocxParagraph *> m_paragraphs;
    QXmlStreamReader m_xmlReader;
};
}

#endif // DOCXXMLREADER_H
