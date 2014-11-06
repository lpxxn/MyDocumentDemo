#include <QtTest>
#include <QString>
#include <QDebug>
#include <QByteArray>
#include <QFile>
#include <QFont>
#include <QTime>
#include <QColor>

#include "relationships.h"
#include "docxzipwriter.h"
#include "abstractooxmlfile.h"
#include "contenttypes.h"
#include "docpropsapp.h"
#include "docpropscore.h"
#include "docxtheme.h"
#include "docxfonttable.h"
#include "docxsettings.h"
#include "docxwebsetting.h"
#include "docxstyle.h"
#include "docxdocument.h"


using namespace TDocx;

class TestRelationShips : public QObject
{
    Q_OBJECT

public:
    TestRelationShips();

private Q_SLOTS:
    void testRelation();
    void mytestFun();

};


TestRelationShips::TestRelationShips()
{

}

void TestRelationShips::testRelation()
{
    // _rels/.rels
    Relationships ships;
    ships.addDocumentRelationship(QStringLiteral("/officeDocument"), QStringLiteral("word/document.xml"));
    ships.addDocumentRelationship(QStringLiteral("/extended-properties"), QStringLiteral("docProps/app.xml"));
    ships.addPackageRelationship(QStringLiteral("/metadata/core-properties"), QStringLiteral("docProps/core.xml"));


    QFile file("testZip.docx");
    file.open(QIODevice::WriteOnly);

    DocxZipWriter writer(&file);
    writer.addFile(QStringLiteral("_rels/.rels"), ships.saveToXmlData());

    // [Content_Types].xml
    ContentTypes contenType(AbstractOOXmlFile::CreateFlag::F_NewFromScratch);
    writer.addFile(QStringLiteral("[Content_Types].xml"), contenType.saveToXmlData());

    // docProps/app.xml
    docPropsApp appXml(AbstractOOXmlFile::CreateFlag::F_NewFromScratch);
    writer.addFile(QStringLiteral("docProps/app.xml"), appXml.saveToXmlData());

    // docProps/core.xml
    docPropsCore corXml(AbstractOOXmlFile::CreateFlag::F_NewFromScratch);
    writer.addFile(QStringLiteral("docProps/core.xml"), corXml.saveToXmlData());

    // word/theme/theme1.xml
    docxTheme theme(AbstractOOXmlFile::CreateFlag::F_NewFromScratch);
    writer.addFile(QStringLiteral("word/theme/theme1.xml"), theme.saveToXmlData());

    // word/_rels/document.xml.rels
    Relationships wordShips;
    wordShips.addDocumentRelationship(QStringLiteral("/settings"), QStringLiteral("settings.xml"));
    wordShips.addDocumentRelationship(QStringLiteral("/styles"), QStringLiteral("styles.xml"));
    wordShips.addDocumentRelationship(QStringLiteral("/theme"), QStringLiteral("theme/theme1.xml"));
    wordShips.addDocumentRelationship(QStringLiteral("/fontTable"), QStringLiteral("fontTable.xml"));
    wordShips.addDocumentRelationship(QStringLiteral("/webSettings"), QStringLiteral("webSettings.xml"));
    writer.addFile(QStringLiteral("word/_rels/document.xml.rels"), wordShips.saveToXmlData());

    docxfontTable fontTable(AbstractOOXmlFile::CreateFlag::F_NewFromScratch);
    writer.addFile(QStringLiteral("word/fontTable.xml"), fontTable.saveToXmlData());

    // word/settings.xml
    DocxSettings setting(AbstractOOXmlFile::CreateFlag::F_NewFromScratch);
    writer.addFile(QStringLiteral("word/settings.xml"), setting.saveToXmlData());

    // word/webSettings.xml
    DocxWebSetting webSet(AbstractOOXmlFile::CreateFlag::F_NewFromScratch);
    writer.addFile(QStringLiteral("word/webSettings.xml"), webSet.saveToXmlData());

    // word/styles.xml
    DocxStyle style(AbstractOOXmlFile::CreateFlag::F_NewFromScratch);
    writer.addFile(QStringLiteral("word/styles.xml"), style.saveToXmlData());

    // word/document.xml
    Document document(AbstractOOXmlFile::CreateFlag::F_NewFromScratch);
    document.writeln("aaaabbbbbb");
    DocxFont font("方正舒体");
    font.setBold(true);
    document.writeln("中文测试中文测试中文测试中文测试中文测试中文测试中文测试中文测试中文测试中文测试中文测试中文测试中文测试中文测试中文测试中文测试中文测试中文测试中文测试",
                     font);
    font.setSize(50);
    font.setItalic(true);
    font.setUnderline(DocxUnderline::Double);
    font.setColor(Qt::green);
    document.writeln("测试大小", font);
    writer.addFile(QStringLiteral("word/document.xml"), document.saveToXmlData());

    writer.close();


}

void TestRelationShips::mytestFun()
{
    QByteArray byte("宋体");
    QByteArray hexBy = byte.toHex();
    qDebug() << hexBy;

}

QTEST_APPLESS_MAIN(TestRelationShips)
#include "testrelationships.moc"
