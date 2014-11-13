#ifndef RELATIONSHIPS_H
#define RELATIONSHIPS_H
#include "docx_global.h"
#include "comdatafun.h"

#include <QString>
#include <QList>
#include <QByteArray>
#include <QIODevice>

namespace TDocx
{
struct DocxRelationship
{
    QString id;
    QString type;
    QString target;
};

class DOCX_EXPORT Relationships
{
public:
    Relationships();

    QList<DocxRelationship> documentRelationship(const QString &relativeType) const;
    QList<DocxRelationship> packageRelationship(const QString &relativeType) const;
    QList<DocxRelationship> msPackageRelationship(const QString &relativeType) const;

    void addDocumentRelationship(const QString &relativeType, const QString &target, QString &returnsaveId = QString());
    void addPackageRelationship(const QString &relativeType, const QString &target, QString &returnsaveId = QString());
    void addMsPackageRelationship(const QString &relativeType, const QString &target, QString &returnsaveId = QString());

    QByteArray saveToXmlData() const;
    void saveToXmlFile(QIODevice *device) const;

    virtual ~Relationships();

private:
    QList<DocxRelationship> relationships(const QString &type) const;
    void addRelationship(const QString &type, const QString &target, QString &returnsaveId = QString());

private:
    QList<DocxRelationship> m_relationShips;
};
}

#endif // RELATIONSHIPS_H
