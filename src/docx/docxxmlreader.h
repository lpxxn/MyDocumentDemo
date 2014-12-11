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

    void readMark(ITagElement *parent, const QString &markName);

    void readCommonMark(ITagElement *parent);
    void readfldSimpleMark(ITagElement* parent);

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
    QList<ITagElement *> m_paragraphs;
    QXmlStreamReader m_xmlReader;
};
}

#endif // DOCXXMLREADER_H
