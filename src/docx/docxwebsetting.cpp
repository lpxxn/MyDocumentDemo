#include "docxwebsetting.h"
#include <QString>
#include <QXmlStreamWriter>

#include "itagelement.h"

namespace TDocx
{
const QString mc = QStringLiteral("http://schemas.openxmlformats.org/markup-compatibility/2006");
const QString r = QStringLiteral("http://schemas.openxmlformats.org/officeDocument/2006/relationships");
const QString w = QStringLiteral("http://schemas.openxmlformats.org/wordprocessingml/2006/main");
const QString w14 = QStringLiteral("http://schemas.microsoft.com/office/word/2010/wordml");

DocxWebSetting::DocxWebSetting(CreateFlag flag)
    : AbstractOOXmlFile(flag)
{
    if (flag ==  CreateFlag::F_NewFromScratch)
        initTag();
}

DocxWebSetting::~DocxWebSetting()
{

}

void DocxWebSetting::initTag()
{
    TagElement* element = new TagElement(QStringLiteral("w:optimizeForBrowser"));
    m_tags.append(element);

    element = new TagElement(QStringLiteral("w:allowPNG"));
    m_tags.append(element);
}

void DocxWebSetting::saveToXmlFile(QIODevice *device) const
{
    QXmlStreamWriter writer(device);
    writer.writeStartDocument(QStringLiteral("1.0"), true);
    writer.writeStartElement(QStringLiteral("w:webSettings"));
    writer.writeNamespace(mc, QStringLiteral("mc"));
    writer.writeNamespace(r, QStringLiteral("r"));
    writer.writeNamespace(w, QStringLiteral("w"));
    writer.writeNamespace(w14, QStringLiteral("w14"));
    writer.writeAttribute(mc, QStringLiteral("Ignorable"), QStringLiteral("w14"));

    for (const TagElement* element : m_tags) {
        element->saveToXmlElement(&writer);
    }
    writer.writeEndElement(); // end webSettings
    writer.writeEndElement();
}

bool DocxWebSetting::loadFromXmlFile(QIODevice *device)
{
    return true;
}

}



