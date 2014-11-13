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

//#include "../../../src/docx/docxzipreader.h"
#include "docxzipreader.h"
#include "docxdocument.h"

using namespace TDocx;

class TestZipDemo : public QObject
{
    Q_OBJECT

public:
    TestZipDemo();

private Q_SLOTS:
    void testImageHash();
    void read();
};

const QString chrysanImgName = QStringLiteral(":/images/Chrysanthemum.jpg");
const QString desert = QStringLiteral(":/images/Desert.jpg");

TestZipDemo::TestZipDemo()
{
    Document doc;
    doc.insertImage(chrysanImgName);
    doc.insertImage(desert, QSize(50, 80));

    doc.insertImage(chrysanImgName, QSize(300, 500));
    doc.insertImage(desert, QSize(500, 800));
    doc.saveAs("img.docx");
}

void TestZipDemo::testImageHash()
{

    QImage img(chrysanImgName);
    QByteArray ba;
    QBuffer buffer(&ba);
    buffer.open(QIODevice::WriteOnly);
    img.save(&buffer);
    QByteArray hashKey = QCryptographicHash::hash(ba, QCryptographicHash::Md5);


    QMimeDatabase database;

    QMimeType type = database.mimeTypeForFile(chrysanImgName);
    qDebug() << "suffixes  " << type.preferredSuffix() << "mime Type  " << type.name() << "  ";
    qDebug() << "suffixes  " << type.genericIconName() << "  ";
    QFileInfo fileInfo(chrysanImgName);
    qDebug() << fileInfo.fileName();
    qDebug() << img.width()  << img.widthMM() << img.height() << img.heightMM();
    QImage img2(chrysanImgName);
    if (img == img2) {
        qDebug() << " img same as img2";
    } else {
        qDebug() << " img not same as img2";
    }

    QImage img3(QStringLiteral(":/images/Desert.jpg"));

    if (img == img3) {
        qDebug() << "same";
    } else {
        qDebug() << " img not same as img3";
    }
}
const char fileContent[] = "\x50\x4B\x03\x04\x0A\x00\x00\x00\x00\x00\x8F\x51\x25\x43\x82\x89\xD1\xF7\x05\x00\x00\x00\x05\x00\x00\x00\x09\x00\x00\x00\x68\x65\x6C\x6C\x6F\x2E\x74\x78\x74\x48\x65\x6C\x6C\x6F\x50\x4B\x03\x04\x0A\x00\x00\x00\x00\x00\xB8\x53\x25\x43\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x03\x00\x00\x00\x71\x74\x2F\x50\x4B\x03\x04\x0A\x00\x00\x00\x00\x00\x92\x51\x25\x43\x2E\x19\xFC\x34\x04\x00\x00\x00\x04\x00\x00\x00\x0B\x00\x00\x00\x71\x74\x2F\x78\x6C\x73\x78\x2E\x74\x78\x74\x58\x6C\x73\x78\x50\x4B\x01\x02\x14\x00\x0A\x00\x00\x00\x00\x00\x8F\x51\x25\x43\x82\x89\xD1\xF7\x05\x00\x00\x00\x05\x00\x00\x00\x09\x00\x00\x00\x00\x00\x00\x00\x01\x00\x20\x00\x00\x00\x00\x00\x00\x00\x68\x65\x6C\x6C\x6F\x2E\x74\x78\x74\x50\x4B\x01\x02\x14\x00\x0A\x00\x00\x00\x00\x00\xB8\x53\x25\x43\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x03\x00\x00\x00\x00\x00\x00\x00\x00\x00\x10\x00\x00\x00\x2C\x00\x00\x00\x71\x74\x2F\x50\x4B\x01\x02\x14\x00\x0A\x00\x00\x00\x00\x00\x92\x51\x25\x43\x2E\x19\xFC\x34\x04\x00\x00\x00\x04\x00\x00\x00\x0B\x00\x00\x00\x00\x00\x00\x00\x01\x00\x20\x00\x00\x00\x4D\x00\x00\x00\x71\x74\x2F\x78\x6C\x73\x78\x2E\x74\x78\x74\x50\x4B\x05\x06\x00\x00\x00\x00\x03\x00\x03\x00\xA1\x00\x00\x00\x7A\x00\x00\x00\x00\x00";
void TestZipDemo::read()
{
    QByteArray data(fileContent, sizeof(fileContent) - 1);
    QBuffer buffer(&data);
    buffer.open(QIODevice::ReadOnly);


    DocxZipReader reader(&buffer);

    QStringList files = reader.filePaths();
    QVERIFY(files.contains("hello.txt"));
    QVERIFY(files.contains("qt/xlsx.txt"));
    QCOMPARE(reader.fileData("hello.txt"), QByteArray("Hello"));
    QCOMPARE(reader.fileData("qt/xlsx.txt"), QByteArray("Xlsx"));

    DocxZipReader readerDoc("test.docx.zip");
    QStringList docfiles = readerDoc.filePaths();
    for (const QString str : docfiles) {
        qDebug() << str;
    }
}


QTEST_APPLESS_MAIN(TestZipDemo)

#include "testszipread.moc"
