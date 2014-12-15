#ifndef DOCXXMLREADER_H
#define DOCXXMLREADER_H
#include "docx_global.h"
#include "docxparagraph.h"
#include "mergetable.h"
#include <QXmlStreamReader>

namespace TDocx
{
class DocxXmlReader;
class TableMergeInfo
{
public:
    TableMergeInfo();
    TableMergeInfo(DocxXmlReader *xmlReader, ITagElement *parent =  nullptr);
    void setParent(TagElement *parent);
    QString tableName() const;
    void setTableName(const QString &name);
    void setEndTableMark();
    void clearInfo();
    bool isValid();
    void appendMarks(const QString markName, ITagElement *parent);

    TagElement *mergeTableElement(int rowIndex, QList<QString> cols);
    TagElement *mergeParagraphElement(QString str, int rowIndex, QList<QString> cols);
    TagElement *mergeRunElement(QString str, int rowIndex, QList<QString> cols);

private:
    QStringList m_marks;
    QString m_tableName;
    ITagElement *m_parent;
    DocxXmlReader *m_xmlReader;
};

class DOCX_EXPORT DocxXmlReader
{
public:
    DocxXmlReader(QIODevice *device);
    DocxXmlReader(const QByteArray &data);
    void readStartElement();
    //void readStartElement(DocxParagraph * parent);

    void readMark(ITagElement *parent, const QString &markName);
    void readPeleMark(DocxParagraph *parent, const QString &markName);

    void readCommonMark(ITagElement *parent, ITagElement *preParent = nullptr);
    void readcomplesFieldsMark(ITagElement* parent, ITagElement *preParent = nullptr);
    void readfldSimpleMark(ITagElement* parent, ITagElement *preParent = nullptr);

    QString elementName() const;
    QByteArray saveToXmlData();
    void saveElement(QXmlStreamWriter *writer);
    void addSignalMergeElement(const QString &name, const QString &value);
    void addMergeTable(MergeTable *table);
    bool isEndElement(const QString &markName);

private:
    void addMarketAtributes(DocxParagraph *para);
    void addMarketAtributes(TagElement *element);
    bool readNextMark();
    void checkSkipMark();

private:
    QList<ITagElement *> m_paragraphs;
    QXmlStreamReader m_xmlReader;
    TableMergeInfo m_tableMergeInfo;
    MergeTable *m_table = nullptr;
    QMap<QString, QString> m_singleEles;
    friend class TableMergeInfo;

};



}

#endif // DOCXXMLREADER_H
