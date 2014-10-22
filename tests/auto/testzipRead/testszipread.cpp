#include <QtTest>
#include <QString>
#include "../../../src/docx/docxzipreader.h"

#include "QDebug"

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
qDebug() << "haha";
}


QTEST_APPLESS_MAIN(TestZipDemo)

#include "testszipread.moc"
