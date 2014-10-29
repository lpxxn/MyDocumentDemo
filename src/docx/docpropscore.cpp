#include "docpropscore.h"
#include <QXmlStreamWriter>
#include <QDateTime>

namespace TDocx
{

docPropsCore::docPropsCore(CreateFlag flag)
    : AbstractOOXmlFile(flag)
{
}


void docPropsCore::saveToXmlFile(QIODevice *device) const
{
    QString xsi =QStringLiteral(R"~(http://www.w3.org/2001/XMLSchema-instance)~");
    QString dcmitype = QStringLiteral(R"~(http://purl.org/dc/dcmitype/)~");
    QString dcterms = QStringLiteral(R"~(http://purl.org/dc/terms/)~");
    QString dc = QStringLiteral(R"~(http://purl.org/dc/elements/1.1/)~");
    QString cp = QStringLiteral(R"~(http://schemas.openxmlformats.org/package/2006/metadata/core-properties)~");

    QXmlStreamWriter writer(device);

    writer.writeStartDocument(QStringLiteral("1.0"), true);
    writer.writeStartElement(QStringLiteral("cp:coreProperties"));
    writer.writeNamespace(xsi, QStringLiteral("xsi"));
    writer.writeNamespace(dcmitype, QStringLiteral("dcmitype"));
    writer.writeNamespace(dcterms, QStringLiteral("dcterms"));
    writer.writeNamespace(dc, QStringLiteral("dc"));
    writer.writeNamespace(cp, QStringLiteral("cp"));

    writer.writeTextElement(dc, QStringLiteral("creator"), QStringLiteral("Peng.li"));
    writer.writeTextElement(cp, QStringLiteral("lastModifiedBy"), QStringLiteral("Peng.li"));
    writer.writeTextElement(cp, QStringLiteral("revision"), QStringLiteral("1"));

    writer.writeStartElement(dcterms, QStringLiteral("created"));
    writer.writeAttribute(xsi, QStringLiteral("type"), QStringLiteral("dcterms:W3CDTF"));
    writer.writeCharacters(QDateTime::currentDateTime().toString());
    writer.writeEndElement();

    writer.writeStartElement(dcterms, QStringLiteral("modified"));
    //writer.writeTextElement(dcterms, QStringLiteral("modified"), QStringLiteral("2014-10-27T14:18:00Z"));
    writer.writeAttribute(xsi, QStringLiteral("type"), QStringLiteral("dcterms:W3CDTF"));
    writer.writeCharacters(QDateTime::currentDateTime().toString());
    writer.writeEndElement();

    writer.writeEndElement();
    writer.writeEndDocument();
}

bool docPropsCore::loadFromXmlFile(QIODevice *device)
{
    return true;
}


}


