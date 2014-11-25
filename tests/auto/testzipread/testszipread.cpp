#include <QtTest>
#include <QString>
#include <QDebug>
#include <QBuffer>
#include <QImage>
#include <QByteArray>
#include <QBuffer>
#include <QCryptographicHash>
#include <QMimeType>
#include <QMimeDatabase>
#include <QFileInfo>
#include <QMap>
#include <QMapIterator>
#include <QDomDocument>
#include <QFile>

#include "docxzipwriter.h"
#include "docxzipreader.h"
#include "docxdocument.h"
#include "contenttypes.h"
#include "mergetable.h"

using namespace TDocx;

class TestZipDemo : public QObject
{
    Q_OBJECT

public:
    TestZipDemo();

private Q_SLOTS:
    void loadTest();
    void testMerge();
    void read();
};

TestZipDemo::TestZipDemo()
{

}

void TestZipDemo::loadTest()
{
    QFile file(QStringLiteral(":/testDoc.zip"));

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << " read Error";
        return;
    }

    DocxZipReader reader(&file);
    QStringList filePaths = reader.filePaths();

    //Load Content_Types file
    if (!filePaths.contains(QLatin1String("[Content_Types].xml")))
        qDebug() << " content Error";

    ContentTypes type(Document::CreateFlag::F_LoadFromExists);
    type.loadFromXmlData(reader.fileData(QStringLiteral("[Content_Types].xml")));
    QByteArray data = type.saveToXmlData();

    DocxZipWriter writer("context.zip");
    writer.addFile(QLatin1String("[Content_Types].xml"), data);

    QMapIterator<QString, QString> contentFile(type.contentFiles());
    while (contentFile.hasNext()) {
        contentFile.next();
        qDebug() << contentFile.key();

    }

    writer.close();
}

void TestZipDemo::testMerge()
{
//    MergeTable table("table1");
//    table.setHorizontalHeaderLabels(QStringList()<< "id" << "name" << "age");
//    QList<QStandardItem *> row;
//    row.append(new QStandardItem("1"));
//    row.append(new QStandardItem("zhangsan"));
//    row.append(new QStandardItem("20"));
//    table.appendRow(row);
//    row.clear();
//    row.append(new QStandardItem("2"));
//    row.append(new QStandardItem("lisi"));
//    row.append(new QStandardItem("19"));
//    table.appendRow(row);

//    row.clear();
//    row.append(new QStandardItem("3"));
//    row.append(new QStandardItem("wangwu"));
//    row.append(new QStandardItem("9"));
//    table.appendRow(row);

//    row.clear();
//    row.append(new QStandardItem("4"));
//    row.append(new QStandardItem("zhaoliu"));
//    row.append(new QStandardItem("9"));
//    table.appendRow(row);

//    for (int r = 0; r < table.rowCount(); r++)
//    {
//        for (int col = 0; col < table.columnCount(); col++) {
//            QStandardItem *item = table.item(r, col);
//            qDebug() << "Table element " << item->text();
//        }
//    }

    QString strName = QStringLiteral("doc.zip");
    QDomDocument xmlDom;

    QFile file(QStringLiteral("://merge.zip"));
    //QFile file(strName);
    if (!file.open(QIODevice::ReadWrite)) {
        qDebug() << " read Error";
        return;
    }

    DocxZipReader reader(&file);
    QStringList filePaths = reader.filePaths();

    //Load Content_Types file
    if (!filePaths.contains(QLatin1String("word/document.xml")))
        qDebug() << " content Error";


    xmlDom.setContent(reader.fileData(QLatin1String("word/document.xml")));
    QDomElement root = xmlDom.documentElement();
    qDebug() << root.text();
    QDomNodeList nodes = xmlDom.elementsByTagName(QStringLiteral("w:fldSimple"));
    qDebug() << nodes.count();

    for (int i = 0; i < nodes.count(); i++) {
        QDomNode ele = nodes.at(i);
        QDomNode parent = ele.parentNode();
        QDomElement newNode = xmlDom.createElement(QStringLiteral("w:r"));
        QDomElement newRun =xmlDom.createElement(QStringLiteral("w:t"));
        QDomText newText = xmlDom.createTextNode(QStringLiteral("hehe"));


        newRun.appendChild(newText);
        newNode.appendChild(newRun);
        parent.insertAfter(newNode, ele);
    }

    QTextStream out(reader.fileData(QLatin1String("word/document.xml")));
    //xmlDom.save(out, 4);



//    if (QFile::copy("://merge.zip", strName))
//        qDebug() << "copy error";

//    QFile fileout(strName);
//    if (fileout.open(QIODevice::WriteOnly))
//        qDebug() << "writeError";
    //DocxZipWriter writer(&file);

    DocxZipWriter writer(strName);
    writer.addFile(QLatin1String("document1.xml"), xmlDom.toByteArray());
    writer.addFile(QLatin1String("document2.xml"), xmlDom.toByteArray());
}


void TestZipDemo::read()
{    
    QFile file(QStringLiteral(":/testDoc.zip"));

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << " read Error";
        return;
    }

    DocxZipReader reader(&file);

    QStringList files = reader.filePaths();

    QVERIFY(files.contains("[Content_Types].xml"));
    QVERIFY(files.contains("_rels/.rels"));
}


QTEST_APPLESS_MAIN(TestZipDemo)

#include "testszipread.moc"
