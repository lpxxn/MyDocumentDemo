#include "contenttypes.h"
#include <QXmlStreamWriter>
#include <QDebug>

namespace TDocx
{

ContentTypes::ContentTypes(CreateFlag flag)
    : AbstractOOXmlFile(flag)
{
    m_package_prefix = QStringLiteral("application/vnd.openxmlformats-package");
    m_document_prefix = QStringLiteral("application/vnd.openxmlformats-officedocument");
    m_msword_prefix = QStringLiteral("application/vnd.ms-word");

    m_defaults.insert(QStringLiteral("rels"), m_package_prefix + QStringLiteral(".relationships+xml"));
    m_defaults.insert(QStringLiteral("xml"), QStringLiteral("application/xml"));

}

void ContentTypes::addDefault(const QString &key, const QString &value)
{
    m_defaults.insert(key, value);
}

void ContentTypes::addOverride(const QString &key, const QString &value)
{
    m_overrides.insert(key, value);
}

void ContentTypes::addOverrideDefault()
{
    m_overrides.insert(QStringLiteral("/word/document.xml"), m_document_prefix + QStringLiteral(".wordprocessingml.document.main+xml"));
    m_overrides.insert(QStringLiteral("/word/styles.xml"), m_document_prefix + QStringLiteral(".wordprocessingml.styles+xml"));
    m_overrides.insert(QStringLiteral("/word/stylesWithEffects.xml"), m_msword_prefix + QStringLiteral(".stylesWithEffects+xml"));
    m_overrides.insert(QStringLiteral("/word/settings.xml"), m_document_prefix + QStringLiteral(".wordprocessingml.settings+xml"));
    m_overrides.insert(QStringLiteral("/word/webSettings.xml"), m_document_prefix + QStringLiteral(".wordprocessingml.webSettings+xml"));
    m_overrides.insert(QStringLiteral("/word/fontTable.xml"), m_document_prefix + QStringLiteral(".wordprocessingml.fontTable+xml"));
    m_overrides.insert(QStringLiteral("/word/theme/theme1.xml"), m_document_prefix + QStringLiteral(".theme+xml"));
    m_overrides.insert(QStringLiteral("/docProps/core.xml"), m_package_prefix + QStringLiteral(".core-properties+xml"));
    m_overrides.insert(QStringLiteral("/docProps/app.xml"), m_document_prefix + QStringLiteral(".extended-properties+xml"));
}


void ContentTypes::saveToXmlFile(QIODevice *device) const
{
    QXmlStreamWriter writer(device);

    writer.writeStartDocument(QStringLiteral("1.0"), true);
    writer.writeStartElement(QStringLiteral("Types"));
    writer.writeAttribute(QStringLiteral("xmlns"), QStringLiteral("http://schemas.openxmlformats.org/package/2006/content-types"));

    QMapIterator<QString, QString> defaultIt(m_defaults);
    while (defaultIt.hasNext()) {
        defaultIt.next();
        writer.writeStartElement(QStringLiteral("Default"));
        writer.writeAttribute(QStringLiteral("Extension"), defaultIt.key());
        writer.writeAttribute(QStringLiteral("ContentType"), defaultIt.value());
        writer.writeEndElement(); // end Defalut
    }

    QMapIterator<QString, QString> overrideIt(m_overrides);
    while (overrideIt.hasNext()) {
        overrideIt.next();
        writer.writeStartElement(QStringLiteral("Override"));
        writer.writeAttribute(QStringLiteral("PartName"), overrideIt.key());
        writer.writeAttribute(QStringLiteral("ContentType"), overrideIt.value());
        writer.writeEndElement(); // end Override
    }

    writer.writeEndElement(); // end Types
    writer.writeEndDocument();
}

bool ContentTypes::loadFromXmlFile(QIODevice *device)
{
    m_defaults.clear();
    m_overrides.clear();
    QXmlStreamReader reader(device);
    while (reader.atEnd()) {
        QXmlStreamReader::TokenType token = reader.readNext();
        if (token == QXmlStreamReader::StartElement) {
            if (reader.name() == QLatin1String("Default")) {
                QXmlStreamAttributes attrs = reader.attributes();
                QString extension =  attrs.value(QLatin1String("Extension")).toString();
                QString type = attrs.value(QLatin1String("ContentType")).toString();
                m_defaults.insert(extension, type);
            }
        } else if (reader.name() == QLatin1String("Override")) {
            QXmlStreamAttributes attrs = reader.attributes();
            QString name =  attrs.value(QLatin1String("PartName")).toString();
            QString type = attrs.value(QLatin1String("ContentType")).toString();
            m_overrides.insert(name, type);
        }
        if (reader.hasError()) {
            qDebug() << QStringLiteral("ContentTypes read error :") << reader.errorString();
        }
    }

    return true;
}

}
