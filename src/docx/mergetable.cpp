#include "mergetable.h"


namespace TDocx
{


MergeTableCol::MergeTableCol()
{

}

void MergeTableCol::append(const QString &value)
{
    m_cols.append(value);
}

QString MergeTableCol::at(int i)
{
    return m_cols.at(i);
}

MergeTable::MergeTable(const QString &tableName) :
    m_tableName(tableName)
{
}

QString MergeTable::tableName() const
{
    return m_tableName;
}

void MergeTable::setTableName(const QString &tableName)
{
    m_tableName = tableName;
}

void MergeTable::addColumn(const QString &colName)
{
    m_cols.append(colName.toUpper());
    m_rows.append(new MergeTableCol());
    m_colCount ++;
}

void MergeTable::addColumn(const std::initializer_list<QString> &cols)
{
    for (const QString &str : cols) {
        m_cols.append(str.toUpper());
        m_rows.append(new MergeTableCol());
    }
    m_colCount += cols.size();
}

QString MergeTable::value(int col, int row) const
{
    MergeTableCol *tcol = m_rows.at(col);
    return tcol->at(row);
}

void MergeTable::addRow(const std::initializer_list<QString> &cols)
{
    int isize = m_cols.size() - cols.size();
    if (isize < 0)
        Q_ASSERT(false);
    int colIndex = 0;
    for (const QString &str : cols) {        
        MergeTableCol *tcol = m_rows.at(colIndex);
        tcol->append(str);
        colIndex++;
    }
    while(isize > 0) {
        MergeTableCol *tcol = m_rows.at(m_rows.size() - isize);
         tcol->append("");
        isize--;
    }
    m_rowCount++;
}

int MergeTable::rowCount()
{
    return m_rowCount;
}

MergeTable::~MergeTable()
{
    qDeleteAll(m_rows);
}

QList<QString> MergeTable::cols() const
{
    return m_cols;
}

void MergeTable::setCols(const QStringList &cols)
{
    m_cols = cols;
}




}
