#ifndef DOCXTABLE_H
#define DOCXTABLE_H
#include "docxparagraph.h"
#include "docx_global.h"
#include "docxmediafile.h"

#include <QString>

#include <initializer_list>

namespace TDocx
{
class AbstractDocument;

class DOCX_EXPORT DocxTableCell : ISaveToXml
{
public:
    DocxTableCell();
    int count() const;
    void saveToXmlElement(QXmlStreamWriter *writer) const;
    void addParagraph(DocxParagraph * paragraph);

    virtual ~DocxTableCell();

private:
    QVector<DocxParagraph *> m_pars;
};

class DOCX_EXPORT DocxTableRow : ISaveToXml
{
public:
    DocxTableRow();
    void addCell(DocxTableCell *cell);
    int count() const;
    DocxTableCell *at(int i);
    DocxTableCell *last();
    void insertImage(const QString &imgName, const QSize &size);
    QVector<DocxTableCell *> row() const;
    void saveToXmlElement(QXmlStreamWriter *writer) const;
    void checkCellsContent();

    virtual ~DocxTableRow();

private:
    QVector<DocxTableCell *> m_row;
};

class DOCX_EXPORT DocxTable : public DocxParagraph
{
public:
    DocxTable(AbstractDocument *doc);
    void saveToXmlElement(QXmlStreamWriter *writer) const;
    void initTableStyle();

    void inertCell();
    void endRow();
    DocxTableRow *lastRow();
    void writeln(const QString &text, const DocxFont &font = DocxFont());
    void insertImage(const QString &imgPath, const QSize &size = QSize());
    void insertElement(const TagElement* ele);

    virtual ~DocxTable();

    RunAlignment cellFormat() const;
    void setCellFormat(const RunAlignment &cellFormat);

    void paragraphStyle(DocxParagraph *p);
private:
    void calculateCellCount(DocxTableRow *row);

private:
    TagElement *m_tblPr;
    int m_cellCount = 0;
    DocxTableRow *m_currentRow;
    QVector<DocxTableRow*> m_rows;
    AbstractDocument *m_doc;
    RunAlignment m_runFormat = RunAlignment::None;

};
}

#endif // DOCXTABLE_H
