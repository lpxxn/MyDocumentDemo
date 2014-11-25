#ifndef MERGETABLE_H
#define MERGETABLE_H

#include "docx_global.h"
#include <QStandardItemModel>

namespace TDocx
{
class DOCX_EXPORT MergeTable : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit MergeTable(const QString &tableName, QObject *parent = 0);

    QString tableName() const;
    void setTableName(const QString &tableName);

signals:

public slots:

private:
    QString m_tableName;


};
}

#endif // MERGETABLE_H
