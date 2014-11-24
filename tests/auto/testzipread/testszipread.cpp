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
    void read();
};

TestZipDemo::TestZipDemo()
{

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
