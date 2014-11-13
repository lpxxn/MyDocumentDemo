#include "relationships.h"
#include <QXmlStreamWriter>
#include <QBuffer>

namespace TDocx
{

//  e.g .rels or document.xml.rels : outermost layer
const QString schema_package = QStringLiteral("http://schemas.openxmlformats.org/package/2006/relationships");

// e.g .rels :  officeDocument" Target="word/document.xml"
const QString schema_doc = QStringLiteral("http://schemas.openxmlformats.org/officeDocument/2006/relationships");

// e.g document.xml.rels :  stylesWithEffects" Target="stylesWithEffects.xml"
const QString schema_msPackage = QStringLiteral("http://schemas.microsoft.com/office/2007/relationships");

Relationships::Relationships()
{
}

QList<DocxRelationship> Relationships::documentRelationship(const QString &relativeType) const
{
    return relationships(schema_doc + relativeType);
}

QList<DocxRelationship> Relationships::packageRelationship(const QString &relativeType) const
{
    return relationships(schema_package + relativeType);
}

QList<DocxRelationship> Relationships::msPackageRelationship(const QString &relativeType) const
{
    return relationships(schema_msPackage + relativeType);
}

void Relationships::addDocumentRelationship(const QString &relativeType, const QString &target, QString &returnsaveId)
{
    addRelationship(schema_doc + relativeType, target, returnsaveId);
}

void Relationships::addPackageRelationship(const QString &relativeType, const QString &target, QString &returnsaveId)
{
    addRelationship(schema_package + relativeType, target, returnsaveId);
}

void Relationships::addMsPackageRelationship(const QString &relativeType, const QString &target, QString &returnsaveId)
{
    addRelationship(schema_msPackage + relativeType, target, returnsaveId);
}

QByteArray Relationships::saveToXmlData() const
{
    QByteArray data;
    QBuffer buffer(&data);
    buffer.open(QIODevice::WriteOnly);
    saveToXmlFile(&buffer);
    return data;
}

/*!
 * \brief 保存为xml
 *
 * e.g
 * <?xml version="1.0" encoding="UTF-8" standalone="yes"?>
 *  --<Relationships>
 *      --<Relationship    Id=""     Type=""    Target="" />
 *      --<Relationship    Id=""     Type=""    Target="" />
 *  --</Relationships>
 */
void Relationships::saveToXmlFile(QIODevice *device) const
{
    QXmlStreamWriter writer(device);
    writer.writeStartDocument(QStringLiteral("1.0"), true);
    writer.writeStartElement(QStringLiteral("Relationships"));
    writer.writeAttribute(QStringLiteral("xmlns"), QStringLiteral("http://schemas.openxmlformats.org/package/2006/relationships"));
    for (DocxRelationship ship : m_relationShips) {
        writer.writeStartElement(QStringLiteral("Relationship"));
        writer.writeAttribute(QStringLiteral("Id"), ship.id);
        writer.writeAttribute(QStringLiteral("Type"), ship.type);
        writer.writeAttribute(QStringLiteral("Target"), ship.target);
        writer.writeEndElement(); // end Relationship
    }
    writer.writeEndElement(); // end Relationships
    writer.writeEndDocument();// end xml Document
}

Relationships::~Relationships()
{

}

QList<DocxRelationship> Relationships::relationships(const QString &type) const
{
    QList<DocxRelationship> res;
    for (DocxRelationship ship : m_relationShips) {
        if (ship.type == type)
        res.append(ship);
    }
    return res;
}

void Relationships::addRelationship(const QString &type, const QString &target, QString &returnsaveId)
{
    DocxRelationship relactionship;
    relactionship.id = ridStr + QString::number(m_relationShips.size() + 1);
    returnsaveId = relactionship.id;
    relactionship.type = type;
    relactionship.target = target;
    m_relationShips.append(relactionship);
}
}
