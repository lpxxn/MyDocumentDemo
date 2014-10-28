#include <QtTest>
#include <QString>
#include <QDebug>
#include <QByteArray>
#include <QFile>
#include "relationships.h"
#include "docxzipwriter.h"
#include "abstractooxmlfile.h"
#include "contenttypes.h"

using namespace TDocx;

class TestRelationShips : public QObject
{
    Q_OBJECT

public:
    TestRelationShips();

private Q_SLOTS:
    void testRelation();

};


TestRelationShips::TestRelationShips()
{

}

void TestRelationShips::testRelation()
{
    // _rels/.rels
    Relationships ships;
    ships.addDocumentRelationship(QStringLiteral("/extended-properties"), QStringLiteral("docProps/app.xml"));
    ships.addPackageRelationship(QStringLiteral("/metadata/core-properties"), QStringLiteral("docProps/core.xml"));
    ships.addDocumentRelationship(QStringLiteral("/officeDocument"), QStringLiteral("word/document.xml"));

    QFile file("testZip.zip");
    file.open(QIODevice::WriteOnly);

    DocxZipWriter writer(&file);
    writer.addFile(QStringLiteral("_rels/.rels"), ships.saveToXmlData());

    // [Content_Types].xml
    ContentTypes contenType(AbstractOOXmlFile::CreateFlag::F_NewFromScratch);
    contenType.addOverrideDefault();
    writer.addFile(QStringLiteral("[Content_Types].xml"), contenType.saveToXmlData());

}

QTEST_APPLESS_MAIN(TestRelationShips)
#include "testrelationships.moc"
