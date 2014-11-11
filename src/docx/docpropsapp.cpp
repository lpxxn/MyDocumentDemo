#include "docpropsapp.h"

#include <QString>
#include <QXmlStreamWriter>
#include <QMap>
#include <QDebug>

const QString p_Template = QStringLiteral("Template");
const QString p_TotalTime = QStringLiteral("TotalTime");
const QString p_Pages = QStringLiteral("Pages");
const QString p_Words = QStringLiteral("Words");
const QString p_Characters = QStringLiteral("Characters");
const QString p_Application = QStringLiteral("Application");
const QString p_Lines = QStringLiteral("Lines");

namespace TDocx
{
DocPropsApp::DocPropsApp(CreateFlag flag)
    : AbstractOOXmlFile(flag)
{
    if (flag == CreateFlag::F_NewFromScratch)
        initDefaultProperties();
}

void DocPropsApp::initDefaultProperties()
{
    m_properties.insert(p_Template, QStringLiteral("Normal.dotm"));
    m_properties.insert(p_TotalTime, QStringLiteral("0"));
    m_properties.insert(p_Pages, QStringLiteral("1"));
    m_properties.insert(p_Words, QStringLiteral("0"));
    m_properties.insert(p_Characters, QStringLiteral("1"));
    m_properties.insert(p_Application, QStringLiteral("Microsoft Office Word"));
    m_properties.insert(QStringLiteral("DocSecurity"), QStringLiteral("0"));
    m_properties.insert(p_Lines, QStringLiteral("1"));

    m_properties.insert(QStringLiteral("Paragraphs"), QStringLiteral("1"));
    m_properties.insert(QStringLiteral("ScaleCrop"), QStringLiteral("false"));
    m_properties.insert(QStringLiteral("Company"), QStringLiteral("Microsoft"));
    m_properties.insert(QStringLiteral("LinksUpToDate"), QStringLiteral("false"));
    m_properties.insert(QStringLiteral("CharactersWithSpaces"), QStringLiteral("1"));
    m_properties.insert(QStringLiteral("SharedDoc"), QStringLiteral("false"));
    m_properties.insert(QStringLiteral("HyperlinksChanged"), QStringLiteral("false"));
    m_properties.insert(QStringLiteral("AppVersion"), QStringLiteral("12.0000"));

}

void DocPropsApp::addProperty(const QString &name, const QString &value)
{
    m_properties.insert(name, value);
}

void DocPropsApp::modifyProperty(const QString &key, const QString &value)
{
    if (m_properties.contains(key))
        m_properties[key] = value;
}

void DocPropsApp::modifyTemplate(const QString &value)
{
    modifyProperty(p_Template, value);
}

void DocPropsApp::modifyTotalTime(const QString &value)
{
    modifyProperty(p_TotalTime, value);
}

void DocPropsApp::modifyPages(const QString &value)
{
    modifyProperty(p_Pages, value);
}

void DocPropsApp::modifyWords(const QString &value)
{
    modifyProperty(p_Words, value);
}

void DocPropsApp::modifyCharacters(const QString &value)
{
    modifyProperty(p_Characters, value);
}

void DocPropsApp::saveToXmlFile(QIODevice *device) const
{
    QXmlStreamWriter writer(device);

    writer.writeStartDocument(QStringLiteral("1.0"), true);
    writer.writeStartElement(QStringLiteral("Properties"));

    writer.writeDefaultNamespace(QStringLiteral("http://schemas.openxmlformats.org/officeDocument/2006/extended-properties"));
    writer.writeNamespace(QStringLiteral("http://schemas.openxmlformats.org/officeDocument/2006/docPropsVTypes"), QStringLiteral("vt"));
    QMapIterator<QString, QString> propertyIt(m_properties);
    while (propertyIt.hasNext()) {
        propertyIt.next();
        writer.writeTextElement(propertyIt.key(), propertyIt.value());
    }

    writer.writeEndElement(); // end Properties
    writer.writeEndDocument();
}

bool DocPropsApp::loadFromXmlFile(QIODevice *device)
{
    m_properties.clear();

    QXmlStreamReader reader(device);
    while (!reader.atEnd()) {
        QXmlStreamReader::TokenType token = reader.readNext();
        if (token == QXmlStreamReader::StartElement) {
            if (reader.name() == QLatin1String("Properties"))
                continue;
            m_properties.insert(reader.name().toString(), reader.readElementText());
        }
    }

    return true;
}


}


