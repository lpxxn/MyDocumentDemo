#ifndef DOCXXMLREADER_H
#define DOCXXMLREADER_H
#include "docx_global.h"
#include "docxparagraph.h"
#include "mergetable.h"
#include <QXmlStreamReader>

namespace TDocx
{
class ExistDocument;
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
    bool isMerged();
    void appendMarks(const QString markName, ITagElement *parent);

    TagElement *mergeTableElement(int rowIndex, QList<QString> cols);
    TagElement *mergeParagraphElement(QString str, int rowIndex, QList<QString> cols);
    TagElement *mergeSingalElement(QString str, int rowIndex, QList<QString> cols);

private:
    QStringList m_marks;
    QString m_tableName;
    ITagElement *m_parent;
    MergeTable *m_currentTable = nullptr;
    bool m_isMerged = false;
    DocxXmlReader *m_xmlReader;
};

struct MergeImgInfo
{
    QString imgName;
    QString imgPath;
    QSize imgSize;
};

class DOCX_EXPORT DocxXmlReader
{
public:
    DocxXmlReader(QIODevice *device, ExistDocument *doc);
    DocxXmlReader(const QByteArray &data, ExistDocument *doc);
    void readStartElement();

    TagElement *imgElement(const QString &imgName, const QSize &size = QSize());

    void readMark(ITagElement *parent, const QString &markName);
    void readPeleMark(DocxParagraph *parent, const QString &markName);

    void readCommonMark(ITagElement *parent, ITagElement *preParent = nullptr);
    void readcomplesFieldsMark(ITagElement* parent, ITagElement *preParent = nullptr);
    void readfldSimpleMark(ITagElement* parent, ITagElement *preParent = nullptr);

    QString elementName() const;
    QByteArray saveToXmlData();
    void saveElement(QXmlStreamWriter *writer);
    void addSignalMergeElement(const QString &name, const QString &value);
    void addMergeImg(const QString &imgName, const QString &imgPath, const QSize &size = QSize());
    void addMergeTable(MergeTable *table);
    MergeTable *currentTable(const QString &tableName);
    bool isEndElement(const QString &markName);

    ~DocxXmlReader();

    void mergeSinglaElement(QString contentStr, ITagElement *parent, ITagElement *preParent);

private:
    void addMarketAtributes(DocxParagraph *para);
    void addMarketAtributes(TagElement *element);
    bool readNextMark();
    void checkSkipMark();

private:
    QList<ITagElement *> m_paragraphs;
    QXmlStreamReader m_xmlReader;
    TableMergeInfo m_tableMergeInfo;    
    QVector<MergeImgInfo*> m_Imgs;
    QVector<MergeTable *> m_tables;
    QMap<QString, QString> m_singleEles;
    ExistDocument *m_doc;
    friend class TableMergeInfo;

};



}

#endif // DOCXXMLREADER_H
