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
#include "docxtable.h"
#include "footandheader.h"

#include <regex>


using namespace TDocx;

class TestRelationShips : public QObject
{
    Q_OBJECT

public:
    TestRelationShips();

private Q_SLOTS:
    void testHeaderAndFooter();
    void testTable();
    void testListFormat();
    void testDocument();
    void testRelation();
    void testImageHash();
    void mytestFun();

};

const QString chrysanImgName = QStringLiteral(":/images/Chrysanthemum.jpg");
const QString desert = QStringLiteral(":/images/Desert.jpg");
const QString content = R"~(Artist Carrie Paterson has long dreamed of beaming messages
      far out to the emptiness of space. Except her messages would have an extra dimension smell.
      By broadcasting formulae of aromatic chemicals, she says, aliens could reconstruct all sorts
      of whiffs that help to define life on Earth: animal blood and faeces, sweet floral
      and citrus scents or benzene to show our global dependence on the car. This way intelligent
      life forms on distant planets who may not see or hear as we do, says Paterson,
      could explore us through smell, one of the most primitive and ubiquitous senses of all.
      Her idea is only the latest in a list of attempts to hail intelligent life outside of the
      Solar System. Forty years ago this month, the Arecibo radio telescope in Puerto
      Rico sent an iconic picture message into space and we’ve arguably been broadcasting to
      aliens ever since we invented TV and radio.
      However in recent years, astronomers, artists, linguists and
      )~";
  TestRelationShips::TestRelationShips()
{

}

void TestRelationShips::testHeaderAndFooter()
{
    Document document;
    //    QFile file("header.zip");
    //    file.open(QIODevice::WriteOnly);
    //    DocxZipWriter writer(&file);
    FootAndHeader *header = new FootAndHeader(&document, HeaderFooterType::HeaderPrimary);
    header->setAlignment(RunAlignment::Center);
    header->write("aa");
    header->insertImg(chrysanImgName, QSize(200, 20));
    //  writer.addFile(QStringLiteral("header.xml"), header.saveToXmlData());
    //    writer.close();   


    FootAndHeader *footer = new FootAndHeader(&document, HeaderFooterType::FooterPrimary);
    footer->write("bb");
    footer->setAlignment(RunAlignment::Center);
    footer->showNumber();
    footer->write("ddddddd");
    footer->write("cc", RunAlignment::Right);
    document.insertSectionFooterAndHeader({ header, footer });
    //document.setDefaultHeaderOrFooter(footer);
    document.writeln("caaaaaaaaaaaaaaaaaaaaaaa");
    document.writeln(content);
    document.writeln(content);
    document.writeln(content);
    document.writeln(content);


    FootAndHeader *header2 = new FootAndHeader(&document, HeaderFooterType::HeaderPrimary);
    header2->write("TestTitle");
    header2->setAlignment(RunAlignment::Right);
    header2->insertImg(chrysanImgName, QSize(100, 20));
    FootAndHeader *footer2 = new FootAndHeader(&document, HeaderFooterType::FooterPrimary);
    footer2->write("Number");
    footer2->showNumber();
    document.insertSectionFooterAndHeader({ header2, footer2 }, true);
    document.writeln(content);
    document.writeln(content);
    document.writeln(content);
    document.writeln(content);

    document.saveAs("headerfooter.docx");
}

void TestRelationShips::testTable()
{
    Document document;

    DocxFont font("方正舒体");
    font.setSpace(2);
    font.setBold(true);
    font.setItalic(true);

    document.writeln("TableTest", RunAlignment::Center);
    DocxTable *tab = new DocxTable(&document);
    tab->setCellFormat(RunAlignment::Right);
    tab->inertCell();
    tab->writeln("1111");
    tab->inertCell();
    tab->setCellFormat(RunAlignment::Left);
    tab->writeln("222");
    tab->inertCell();
    tab->writeln("333");
    tab->endRow();

    tab->setCellFormat(RunAlignment::Center);
    tab->inertCell();
    tab->writeln(QStringLiteral("bbbb"));
    tab->writeln(QString::fromUtf8("测试测试"), font);
    tab->inertCell();
    tab->writeln(QStringLiteral("abde"));
    tab->inertCell();
    tab->insertImage(chrysanImgName, QSize(200, 200));
    tab->endRow();
    document.insertTable(tab);

    document.saveAs("TableTest.docx");

}

void TestRelationShips::testListFormat()
{
    Document document;

    document.writeln("Bullet");
    DocxListFormat listF(ListFormatStyle::Bullet);
    document.writeList(listF, { QStringLiteral("aab"), QStringLiteral("bbb"), QStringLiteral("bbbb"), QStringLiteral("bbbb") });
    document.writeln("Numer");
    listF.setFlag(ListFormatStyle::Number);
    DocxFont font("方正舒体");
    font.setSpace(2);
    font.setBold(true);
    font.setItalic(true);
    listF.setFont(font);
    document.writeList(listF, { QStringLiteral("aaa"), QStringLiteral("aaaa"), QStringLiteral("aaaa"), QStringLiteral("aaa") });


    document.saveAs(QStringLiteral("listFormat.docx"));
}

void TestRelationShips::testDocument()
{    
    Document document;
    document.writeHeading("标题", HeadingLevel::head1);
    document.writeln("aaaabbbbbb");
    DocxFont font("方正舒体");
    font.setSpace(2);
    font.setBold(true);
    document.writeln(R"~(中文测试中文测试中文测试中文测试中文测试中文测试中文测试中文测试中文测试中文测试中文测试中文测试中文测试中文测试中文测试中文测试中文测试中文测试中文测试)~",
                     font);
    font.setSize(0);
    font.setSize(50);
    font.setFamily("宋体");
    font.setItalic(true);
    font.setUnderline(DocxUnderline::Double);
    font.setColor(Qt::green);


    document.writeln("测试文字内容", font);

    DocxTable *tab = new DocxTable(&document);
    tab->inertCell();
    tab->writeln("1111");
    tab->inertCell();
    tab->writeln("222");
    tab->inertCell();
    tab->writeln("333");
    tab->endRow();

    tab->inertCell();
    tab->writeln(QStringLiteral("bbbb"));
    tab->writeln(QString::fromUtf8("测试测试"), font);
    tab->inertCell();
    tab->writeln(QStringLiteral("abde"));
    tab->inertCell();
    tab->insertImage(chrysanImgName, QSize(200, 200));
    tab->endRow();
    document.insertTable(tab);
    document.writeln();
    document.writeln("测试文字内容");
    font.setItalic(false);
    font.setColor(Qt::red);
    document.writeHeading("标题", HeadingLevel::head2, font);
    document.writeln("测试文字内容");

    document.insertImage(desert, QSize(50, 80));

    document.insertImage(chrysanImgName, QSize(300, 500));
    document.insertImage(desert, QSize(500, 800));

    document.writeHeading("标题", HeadingLevel::head3);
    document.writeln("测试文字内容");
    document.writeHeading("标题", HeadingLevel::head4);
    document.writeln("测试文字内容测试文字内容");
    document.writeHeading("标题", HeadingLevel::head5);
    document.writeln("测试文字内容");
    document.writeHeading("标题", HeadingLevel::head6);
    document.writeln("测试文字内容");
    document.writeHeading("标题", HeadingLevel::head7);
    document.writeln("测试文字内容");

    document.writeln("Bullet");
    DocxListFormat listF(ListFormatStyle::Bullet);
    document.writeList(listF, { QStringLiteral("aab"), QStringLiteral("bbb"), QStringLiteral("bbbb"), QStringLiteral("bbbb") });
    document.writeln("Numer");
    listF.setFlag(ListFormatStyle::Number);

    font.setSpace(2);
    font.setBold(true);
    font.setItalic(true);
    listF.setFont(font);
    document.writeList(listF, { QStringLiteral("aaa"), QStringLiteral("aaaa"), QStringLiteral("aaaa"), QStringLiteral("aaa") });


    document.writeHeading("标题", HeadingLevel::head8);
    document.writeln("测试文字内容");
    document.writeHeading("标题", HeadingLevel::head9);
    document.writeln("测试文字内容");


    DocxFont font2;
    document.writeln("测试大小", font2);

    document.save();
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
    DocPropsApp appXml(AbstractOOXmlFile::CreateFlag::F_NewFromScratch);
    writer.addFile(QStringLiteral("docProps/app.xml"), appXml.saveToXmlData());

    // docProps/core.xml
    DocPropsCore corXml(AbstractOOXmlFile::CreateFlag::F_NewFromScratch);
    writer.addFile(QStringLiteral("docProps/core.xml"), corXml.saveToXmlData());

    // word/theme/theme1.xml
    DocxTheme theme(AbstractOOXmlFile::CreateFlag::F_NewFromScratch);
    writer.addFile(QStringLiteral("word/theme/theme1.xml"), theme.saveToXmlData());

    // word/_rels/document.xml.rels
    Relationships wordShips;
    wordShips.addDocumentRelationship(QStringLiteral("/settings"), QStringLiteral("settings.xml"));
    wordShips.addDocumentRelationship(QStringLiteral("/styles"), QStringLiteral("styles.xml"));
    wordShips.addDocumentRelationship(QStringLiteral("/theme"), QStringLiteral("theme/theme1.xml"));
    wordShips.addDocumentRelationship(QStringLiteral("/fontTable"), QStringLiteral("fontTable.xml"));
    wordShips.addDocumentRelationship(QStringLiteral("/webSettings"), QStringLiteral("webSettings.xml"));
    writer.addFile(QStringLiteral("word/_rels/document.xml.rels"), wordShips.saveToXmlData());

    //word/fontTable.xml
    DocxfontTable fontTable(AbstractOOXmlFile::CreateFlag::F_NewFromScratch);
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
    font.setSpace(2);
    font.setBold(true);
    document.writeln("中文测试中文测试中文测试中文测试中文测试中文测试中文测试中文测试中文测试中文测试中文测试中文测试中文测试中文测试中文测试中文测试中文测试中文测试中文测试",
                     font);
    font.setSize(0);
    font.setSize(50);
    font.setFamily("宋体");
    font.setItalic(true);
    font.setUnderline(DocxUnderline::Double);
    font.setColor(Qt::green);
    document.writeln("测试大小", font);

    DocxFont font2;
    document.writeln("测试大小", font2);
    writer.addFile(QStringLiteral("word/document.xml"), document.saveToXmlData());

    writer.close();


}

void TestRelationShips::testImageHash()
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

void TestRelationShips::mytestFun()
{
    QByteArray byte("宋体");
    QByteArray hexBy = byte.toHex();
    qDebug() << hexBy;

    std::regex r("^Heading[1-9]$");
    int i =1;
    while(i < 12) {
        QString str = QString("Heading%1").arg(QString::number(i));
        if (std::regex_match(str.toStdString(), r))
            qDebug() << "math" << str;
        i++;
    }
}

QTEST_APPLESS_MAIN(TestRelationShips)
#include "testrelationships.moc"
