#ifndef MERGETABLE_H
#define MERGETABLE_H

#include "docx_global.h"
#include <QStandardItemModel>

#include <initializer_list>

namespace TDocx
{
class MergeTableCol
{
public:
    MergeTableCol();
    void append(const QString &value);
    QString at(int i);

private:
    QVector<QString> m_cols;
};

class DOCX_EXPORT MergeTable
{    
public:
    explicit MergeTable(const QString &tableName);

    QString tableName() const;
    void setTableName(const QString &tableName);
    QList<QString> cols() const;
    void setCols(const QStringList &cols);
    void addColumn(const QString &colName);
    void addColumn(const std::initializer_list<QString> &cols);
    QString value(int col, int row) const;
    void addRow(const std::initializer_list<QString> &cols);
    int rowCount();
private:
    QVector<MergeTableCol*> m_rows;
    QString m_tableName;
    QList<QString> m_cols;
    int m_rowCount = 0;
    int m_colCount = 0;
};
}

#endif // MERGETABLE_H
