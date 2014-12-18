#include "docpropscore.h"
#include <QXmlStreamWriter>
#include <QDateTime>

namespace TDocx
{

DocPropsCore::DocPropsCore(CreateFlag flag)
    : AbstractOOXmlFile(flag)
{
}


void DocPropsCore::saveToXmlFile(QIODevice *device) const
{
    QString xsi =QStringLiteral("http://www.w3.org/2001/XMLSchema-instance");
    QString dcmitype = QStringLiteral("http://purl.org/dc/dcmitype/");
    QString dcterms = QStringLiteral("http://purl.org/dc/terms/");
    QString dc = QStringLiteral("http://purl.org/dc/elements/1.1/");
    QString cp = QStringLiteral("http://schemas.openxmlformats.org/package/2006/metadata/core-properties");

    QXmlStreamWriter writer(device);

    writer.writeStartDocument(QStringLiteral("1.0"), true);
    writer.writeStartElement(QStringLiteral("cp:coreProperties"));
    writer.writeNamespace(xsi, QStringLiteral("xsi"));
    writer.writeNamespace(dcmitype, QStringLiteral("dcmitype"));
    writer.writeNamespace(dcterms, QStringLiteral("dcterms"));
    writer.writeNamespace(dc, QStringLiteral("dc"));
    writer.writeNamespace(cp, QStringLiteral("cp"));

    // dc:creator
    writer.writeTextElement(dc, QStringLiteral("creator"), QStringLiteral("Peng.li"));
    // cp:lastModifiedBy
    writer.writeTextElement(cp, QStringLiteral("lastModifiedBy"), QStringLiteral("Peng.li"));
    writer.writeTextElement(cp, QStringLiteral("revision"), QStringLiteral("1"));

    writer.writeStartElement(dcterms, QStringLiteral("created"));
    writer.writeAttribute(xsi, QStringLiteral("type"), QStringLiteral("dcterms:W3CDTF"));
    writer.writeCharacters(QDateTime::currentDateTime().toString(Qt::ISODate));
    writer.writeEndElement();

    writer.writeStartElement(dcterms, QStringLiteral("modified"));

    writer.writeAttribute(xsi, QStringLiteral("type"), QStringLiteral("dcterms:W3CDTF"));
    writer.writeCharacters(QDateTime::currentDateTime().toString(Qt::ISODate));
    writer.writeEndElement();

    writer.writeEndElement();
    writer.writeEndDocument();
}

bool DocPropsCore::loadFromXmlFile(QIODevice *device)
{
    return true;
}

}


