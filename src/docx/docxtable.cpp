#include "docxtable.h"
#include "docxparagraph.h"
#include "docxdocument.h"

#include <QXmlStreamWriter>

namespace TDocx
{

// Cell
DocxTableCell::DocxTableCell()
{

}

int DocxTableCell::count() const
{
    return m_pars.count();
}

void DocxTableCell::saveToXmlElement(QXmlStreamWriter *writer) const
{
    for (const DocxParagraph *ele : m_pars) {
        ele->saveToXmlElement(writer);
    }
}

void DocxTableCell::addParagraph(DocxParagraph *paragraph)
{
    m_pars << paragraph;
}

DocxTableCell::~DocxTableCell()
{
    qDeleteAll(m_pars);
}

// end Cell

// Row

DocxTableRow::DocxTableRow()
{

}

void DocxTableRow::addCell(DocxTableCell *cell)
{
    m_row << cell;
}

int DocxTableRow::count() const
{
    return m_row.count();
}

DocxTableCell *DocxTableRow::at(int i)
{
    return m_row.at(i);
}

DocxTableCell *DocxTableRow::last()
{
    return m_row.last();
}

void DocxTableRow::insertImage(const QString &imgName, const QSize &size)
{

}

QVector<DocxTableCell *> DocxTableRow::row() const
{
    return m_row;
}

DocxTableRow::~DocxTableRow()
{
    qDeleteAll(m_row);
}

void DocxTableRow::checkCellsContent()
{
    for (DocxTableCell *cell : m_row) {
        if (cell->count() == 0)
            cell->addParagraph(new DocxParagraph());
    }
}

void DocxTableRow::saveToXmlElement(QXmlStreamWriter *writer) const
{
    for (const DocxTableCell *cell : m_row) {
        writer->writeStartElement(QStringLiteral("w:tc"));
        writer->writeEmptyElement(QStringLiteral("w:tcPr"));
        cell->saveToXmlElement(writer);
        writer->writeEndElement(); // end w:tc
    }
}

// end Row


DocxTable::DocxTable(Document *doc)
    : DocxParagraph(), m_doc(doc)
{
    m_currentRow =  new DocxTableRow();
    initTableStyle();
}

void DocxTable::saveToXmlElement(QXmlStreamWriter *writer) const
{
    if(!m_cellCount)
        return;
    writer->writeStartElement(QStringLiteral("w:tbl"));

    // table pr
    m_tblPr->saveToXmlElement(writer);


    // child
    ParagraphTagIterator iter = createIterator();
    while(iter.hasNext()) {
        ISaveToXml *ele = iter.next();
        ele->saveToXmlElement(writer);
    }
    for (const DocxTableRow *row : m_rows) {
        writer->writeStartElement(QStringLiteral("w:tr"));
        row->saveToXmlElement(writer);
        writer->writeEndElement();// end w:tr
    }

    writer->writeEndElement();
}

void DocxTable::initTableStyle()
{
    m_tblPr = new TagElement(QStringLiteral("w:tblPr"));

    TagElement *tblw = new TagElement(QStringLiteral("w:tblW"));
    tblw->addProperty(QStringLiteral("w:w"), QStringLiteral("5000"));
    tblw->addProperty(QStringLiteral("w:type"), QStringLiteral("pct"));
    m_tblPr->addChild(tblw);

    // tblBorders
    TagElement *tblBorders = new TagElement(QStringLiteral("w:tblBorders"));

    TagElement *top = new TagElement(QStringLiteral("w:top"));
    top->addProperty(QStringLiteral("w:val"), QStringLiteral("single"));
    top->addProperty(QStringLiteral("w:sz"), QStringLiteral("4"));
    top->addProperty(QStringLiteral("w:space"), QStringLiteral("0"));
    top->addProperty(QStringLiteral("w:color"), QStringLiteral("auto"));
    tblBorders->addChild(top);

    TagElement *left = new TagElement(QStringLiteral("w:left"));
    left->addProperty(QStringLiteral("w:val"), QStringLiteral("single"));
    left->addProperty(QStringLiteral("w:sz"), QStringLiteral("4"));
    left->addProperty(QStringLiteral("w:space"), QStringLiteral("0"));
    left->addProperty(QStringLiteral("w:color"), QStringLiteral("auto"));
    tblBorders->addChild(left);

    TagElement *bottom = new TagElement(QStringLiteral("w:bottom"));
    bottom->addProperty(QStringLiteral("w:val"), QStringLiteral("single"));
    bottom->addProperty(QStringLiteral("w:sz"), QStringLiteral("4"));
    bottom->addProperty(QStringLiteral("w:space"), QStringLiteral("0"));
    bottom->addProperty(QStringLiteral("w:color"), QStringLiteral("auto"));
    tblBorders->addChild(bottom);

    TagElement *right = new TagElement(QStringLiteral("w:right"));
    right->addProperty(QStringLiteral("w:val"), QStringLiteral("single"));
    right->addProperty(QStringLiteral("w:sz"), QStringLiteral("4"));
    right->addProperty(QStringLiteral("w:space"), QStringLiteral("0"));
    right->addProperty(QStringLiteral("w:color"), QStringLiteral("auto"));
    tblBorders->addChild(right);

    TagElement *insideH = new TagElement(QStringLiteral("w:insideH"));
    insideH->addProperty(QStringLiteral("w:val"), QStringLiteral("single"));
    insideH->addProperty(QStringLiteral("w:sz"), QStringLiteral("4"));
    insideH->addProperty(QStringLiteral("w:space"), QStringLiteral("0"));
    insideH->addProperty(QStringLiteral("w:color"), QStringLiteral("auto"));
    tblBorders->addChild(insideH);

    TagElement *insideV = new TagElement(QStringLiteral("w:insideV"));
    insideV->addProperty(QStringLiteral("w:val"), QStringLiteral("single"));
    insideV->addProperty(QStringLiteral("w:sz"), QStringLiteral("4"));
    insideV->addProperty(QStringLiteral("w:space"), QStringLiteral("0"));
    insideV->addProperty(QStringLiteral("w:color"), QStringLiteral("auto"));
    tblBorders->addChild(insideV);

    m_tblPr->addChild(tblBorders);
    // end tblBorders

    //tblCellMar
    TagElement *tblCellMar = new TagElement(QStringLiteral("w:tblCellMar"));
    TagElement *child = new TagElement(QStringLiteral("w:left"));
    child->addProperty(QStringLiteral("w:w"), QStringLiteral("108"));
    child->addProperty(QStringLiteral("w:type"), QStringLiteral("dxa"));
    tblCellMar->addChild(child);
    child = new TagElement(QStringLiteral("w:right"));
    child->addProperty(QStringLiteral("w:w"), QStringLiteral("108"));
    child->addProperty(QStringLiteral("w:type"), QStringLiteral("dxa"));
    tblCellMar->addChild(child);
    m_tblPr->addChild(tblCellMar);
    // end tblCellMar

}

void DocxTable::inertCell()
{
    m_currentRow->addCell(new DocxTableCell());
}

void DocxTable::endRow()
{
    m_currentRow->checkCellsContent();
    calculateCellCount(m_currentRow);
    m_rows.append(m_currentRow);
    m_currentRow =  new DocxTableRow();
}

DocxTableRow *DocxTable::lastRow()
{
    return m_rows.last();
}

void DocxTable::writeln(const QString &text)
{
    DocxTableCell *cell = m_currentRow->last();
    DocxParagraph *p = new DocxParagraph();
    p->setText(text);
    cell->addParagraph(p);
}

void DocxTable::insertImage(const QString &imgPath, const QSize &size)
{
    TagElement *ele = m_doc->m_inserImagePrivate->imageTagElement(imgPath, size);
    DocxTableCell *cell = m_currentRow->last();
    DocxParagraph *p = new DocxParagraph();
    p->addContentElement(ele);
    cell->addParagraph(p);
}

void DocxTable::insertElement(const TagElement *ele)
{

}


DocxTable::~DocxTable()
{

}

void DocxTable::calculateCellCount(DocxTableRow *row)
{
    if (m_cellCount < row->count())
        m_cellCount = row->count();
}


}





