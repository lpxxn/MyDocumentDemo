#include "docxfonttable.h"

#include <QMapIterator>

namespace TDocx
{


const QString wNamespace = "http://schemas.openxmlformats.org/wordprocessingml/2006/main";
const QString mcNamespace = "http://schemas.openxmlformats.org/markup-compatibility/2006";
const QString rNamespace = "http://schemas.openxmlformats.org/officeDocument/2006/relationships";
const QString w14Namespace = "http://schemas.microsoft.com/office/word/2010/wordml";


DocxfontTable::DocxfontTable(CreateFlag flag)
    :AbstractOOXmlFile(flag)
{
    if (flag ==  CreateFlag::F_NewFromScratch)
        initFonts();
}

void DocxfontTable::initFonts()
{
    QVector<ContentInfo> fonts = QVector<ContentInfo>();

    // begin Calibri
    ContentInfo font;
    font.name = QStringLiteral("panose1");
    font.addProperty(QStringLiteral("val"), QStringLiteral("020F0502020204030204"));
    fonts.append(font);

    font = ContentInfo();
    font.name = QStringLiteral("charset");
    font.addProperty(QStringLiteral("val"), QStringLiteral("00"));
    fonts.append(font);

    font = ContentInfo();
    font.name = QStringLiteral("family");
    font.addProperty(QStringLiteral("val"), QStringLiteral("swiss"));
    fonts.append(font);

    font = ContentInfo();
    font.name = QStringLiteral("pitch");
    font.addProperty(QStringLiteral("val"), QStringLiteral("variable"));
    fonts.append(font);

    font = ContentInfo();
    font.name = QStringLiteral("sig");
    font.addProperty(QStringLiteral("usb0"), QStringLiteral("E10002FF"));
    font.addProperty(QStringLiteral("usb1"), QStringLiteral("4000ACFF"));
    font.addProperty(QStringLiteral("usb2"), QStringLiteral("00000009"));
    font.addProperty(QStringLiteral("usb3"), QStringLiteral("00000000"));
    font.addProperty(QStringLiteral("csb0"), QStringLiteral("0000019F"));
    font.addProperty(QStringLiteral("csb1"), QStringLiteral("00000000"));
    fonts.append(font);
    m_fonts.insert(QStringLiteral("Calibri"), fonts);
    // end Calibri

    // begin 宋体
    fonts.clear();
    font = ContentInfo();
    font.name = QStringLiteral("altName");
    font.addProperty(QStringLiteral("val"), QStringLiteral("SimSun"));
    fonts.append(font);

    font = ContentInfo();
    font.name = QStringLiteral("panose1");
    font.addProperty(QStringLiteral("val"), QStringLiteral("02010600030101010101"));
    fonts.append(font);

    font = ContentInfo();
    font.name = QStringLiteral("charset");
    font.addProperty(QStringLiteral("val"), QStringLiteral("86"));
    fonts.append(font);

    font = ContentInfo();
    font.name = QStringLiteral("family");
    font.addProperty(QStringLiteral("val"), QStringLiteral("auto"));
    fonts.append(font);

    font = ContentInfo();
    font.name = QStringLiteral("pitch");
    font.addProperty(QStringLiteral("val"), QStringLiteral("variable"));
    fonts.append(font);

    font = ContentInfo();
    font.name = QStringLiteral("sig");
    font.addProperty(QStringLiteral("usb0"), QStringLiteral("00000003"));
    font.addProperty(QStringLiteral("usb1"), QStringLiteral("288F0000"));
    font.addProperty(QStringLiteral("usb2"), QStringLiteral("00000016"));
    font.addProperty(QStringLiteral("usb3"), QStringLiteral("00000000"));
    font.addProperty(QStringLiteral("csb0"), QStringLiteral("00040001"));
    font.addProperty(QStringLiteral("csb1"), QStringLiteral("00000000"));
    fonts.append(font);
    m_fonts.insert(QString::fromUtf8("宋体"), fonts);
    // end 宋体

    // begin Times New Roman
    fonts.clear();

    font = ContentInfo();
    font.name = QStringLiteral("panose1");
    font.addProperty(QStringLiteral("val"), QStringLiteral("02020603050405020304"));
    fonts.append(font);

    font = ContentInfo();
    font.name = QStringLiteral("charset");
    font.addProperty(QStringLiteral("val"), QStringLiteral("00"));
    fonts.append(font);

    font = ContentInfo();
    font.name = QStringLiteral("family");
    font.addProperty(QStringLiteral("val"), QStringLiteral("roman"));
    fonts.append(font);

    font = ContentInfo();
    font.name = QStringLiteral("pitch");
    font.addProperty(QStringLiteral("val"), QStringLiteral("variable"));
    fonts.append(font);

    font = ContentInfo();
    font.name = QStringLiteral("sig");
    font.addProperty(QStringLiteral("usb0"), QStringLiteral("E0002AFF"));
    font.addProperty(QStringLiteral("usb1"), QStringLiteral("C0007841"));
    font.addProperty(QStringLiteral("usb2"), QStringLiteral("00000009"));
    font.addProperty(QStringLiteral("usb3"), QStringLiteral("00000000"));
    font.addProperty(QStringLiteral("csb0"), QStringLiteral("000001FF"));
    font.addProperty(QStringLiteral("csb1"), QStringLiteral("00000000"));
    fonts.append(font);
    m_fonts.insert(QString::fromUtf8("Times New Roman"), fonts);
    // end Times New Roman

    // begin Cambria
    fonts.clear();

    font = ContentInfo();
    font.name = QStringLiteral("panose1");
    font.addProperty(QStringLiteral("val"), QStringLiteral("02040503050406030204"));
    fonts.append(font);

    font = ContentInfo();
    font.name = QStringLiteral("charset");
    font.addProperty(QStringLiteral("val"), QStringLiteral("00"));
    fonts.append(font);

    font = ContentInfo();
    font.name = QStringLiteral("family");
    font.addProperty(QStringLiteral("val"), QStringLiteral("roman"));
    fonts.append(font);

    font = ContentInfo();
    font.name = QStringLiteral("pitch");
    font.addProperty(QStringLiteral("val"), QStringLiteral("variable"));
    fonts.append(font);

    font = ContentInfo();
    font.name = QStringLiteral("sig");
    font.addProperty(QStringLiteral("usb0"), QStringLiteral("E0002AFF"));
    font.addProperty(QStringLiteral("usb1"), QStringLiteral("400004FF"));
    font.addProperty(QStringLiteral("usb2"), QStringLiteral("00000000"));
    font.addProperty(QStringLiteral("usb3"), QStringLiteral("00000000"));
    font.addProperty(QStringLiteral("csb0"), QStringLiteral("0000019F"));
    font.addProperty(QStringLiteral("csb1"), QStringLiteral("00000000"));
    fonts.append(font);
    m_fonts.insert(QString::fromUtf8("Cambria"), fonts);
    // end Cambria
}



void DocxfontTable::saveFonts(QXmlStreamWriter &writer) const
{
    if (!m_fonts.isEmpty()) {
        QMapIterator<QString, QVector<ContentInfo> > iter(m_fonts);
        while (iter.hasNext()) {
            iter.next();
            writer.writeStartElement(wNamespace, QStringLiteral("font"));
            writer.writeAttribute(wNamespace, QStringLiteral("name"), iter.key());
            for (const ContentInfo &info : iter.value()) {
                writer.writeEmptyElement(wNamespace, info.name);
                for (const QPair<QString, QString> pair : info.values) {
                    writer.writeAttribute(wNamespace, pair.first, pair.second);
                }
            }
            writer.writeEndElement();
        }
    }
}

void DocxfontTable::saveToXmlFile(QIODevice *device) const
{
    QXmlStreamWriter writer(device);
    writer.writeStartDocument(QStringLiteral("1.0"), true);
    writer.writeStartElement(QStringLiteral("w:fonts"));
    writer.writeNamespace(wNamespace, QStringLiteral("w"));
    writer.writeNamespace(mcNamespace, QStringLiteral("mc"));
    writer.writeNamespace(rNamespace, QStringLiteral("r"));
    writer.writeNamespace(w14Namespace, QStringLiteral("w14"));
    writer.writeAttribute(mcNamespace, QStringLiteral("Ignorable"), QStringLiteral("w14"));
    saveFonts(writer);
    writer.writeEndElement(); // end w:fonts
    writer.writeEndDocument();
}

bool DocxfontTable::loadFromXmlFile(QIODevice *device)
{
    return true;
}


}
