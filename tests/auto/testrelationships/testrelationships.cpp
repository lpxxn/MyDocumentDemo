#include <QtTest>
#include <QString>
#include <QDebug>
#include <QByteArray>
#include <QFile>
#include "relationships.h"
#include "docxzipwriter.h"
//#include "../../../src/docx/docxzipwriter.h"

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
    Relationships ships;
    ships.addDocumentRelationship(QStringLiteral("/extended-properties"), QStringLiteral("docProps/app.xml"));
    ships.addPackageRelationship(QStringLiteral("/metadata/core-properties"), QStringLiteral("docProps/core.xml"));
    ships.addDocumentRelationship(QStringLiteral("/officeDocument"), QStringLiteral("docProps/xl/workbook.xml"));
    //QByteArray data = ships.saveToXmlData();
    QFile file("testZip.zip");
    file.open(QIODevice::WriteOnly);

    DocxZipWriter writer(&file);
    writer.addFile(QStringLiteral("_rels/.rels"), ships.saveToXmlData());

}

QTEST_APPLESS_MAIN(TestRelationShips)
#include "testrelationships.moc"
