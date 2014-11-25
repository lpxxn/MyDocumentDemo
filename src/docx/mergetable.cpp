#include "mergetable.h"


namespace TDocx
{
MergeTable::MergeTable(const QString &tableName, QObject *parent) :
    QStandardItemModel(parent), m_tableName(tableName)
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


}
