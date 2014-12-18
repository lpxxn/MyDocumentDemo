#include "docxmediafile.h"
#include "comdatafun.h"
#include "docxdocument.h"

#include <QBuffer>
#include <QMimeType>
#include <QMimeDatabase>
#include <QImage>

namespace TDocx
{
DocxMediaFile::DocxMediaFile(const QString &imageName)
{
    QMimeDatabase database;
    QMimeType type = database.mimeTypeForFile(imageName);
    QImage img(imageName);

    QBuffer buffer(&m_content);
    buffer.open(QIODevice::WriteOnly);
    img.save(&buffer, type.preferredSuffix().toStdString().c_str());
    m_hashKey = ComDataFun::byteHash(m_content);
    m_imgSize = img.size();

    m_suffix = type.preferredSuffix();
    m_mimeType = type.name();
}

QString DocxMediaFile::suffix() const
{
    return m_suffix;
}

QString DocxMediaFile::mimeType() const
{
    return m_mimeType;
}

QByteArray DocxMediaFile::content() const
{
    return m_content;
}

QByteArray DocxMediaFile::hashKey() const
{
    return m_hashKey;
}
QString DocxMediaFile::name() const
{
    return m_name;
}

void DocxMediaFile::setName(const QString &name)
{
    m_name = name;
}
QString DocxMediaFile::Id() const
{
    return m_Id;
}

void DocxMediaFile::setId(const QString &Id)
{
    m_Id = Id;
}
QSize DocxMediaFile::imgSize() const
{
    return m_imgSize;
}

void DocxMediaFile::setImgSize(const QSize &imgSize)
{
    m_imgSize = imgSize;
}
// end DocxMediaFile;

DocxInsertImagePrivate::DocxInsertImagePrivate(AbstractDocument *doc)
    : m_doc(doc)
{

}

/*!
 * \brief return image tag
 *
 * return same image tag in different xml files.
 * the first image tag content detail style in each xml file
 * \param imgName
 * \param size
 * \return
 */
TagElement *DocxInsertImagePrivate::imageTagElement(const QString &imgName, const QSize &size, bool firstImg)
{
    DocxMediaFile *mediaFile =  mediafileInfo(imgName);

    TagElement *pict = imageTagElement(mediaFile, size, firstImg);

    return pict;
}

TagElement * DocxInsertImagePrivate::imageTagElement(DocxMediaFile *mediaFile, const QSize &size, bool firstImg)
{
    TagElement *pict = new TagElement(QStringLiteral("w:pict"));

    if (firstImg)
        pict->addChild(shapetypeStyle());

    TagElement *shap = new TagElement(QStringLiteral("v:shape"));
    shap->addProperty(QStringLiteral("id"), QString("_x0000_i") + QString::number(1000 + m_imgs.count()));
    shap->addProperty(QStringLiteral("type"), QStringLiteral("#_x0000_t75"));
    if (size.isValid())
        shap->addProperty(QStringLiteral("style"), QString("height:%1pt;width:%2pt").arg(size.height()).arg(size.width()));
    else
        shap->addProperty(QStringLiteral("style"), QString("height:%1pt;width:%2pt").arg(mediaFile->imgSize().height()).arg(mediaFile->imgSize().width()));

    TagElement *shapChild = new TagElement(QStringLiteral("v:imagedata"));
    shapChild->addProperty(QStringLiteral("r:id"), mediaFile->Id());
    shapChild->addProperty(QStringLiteral("o:title"), QStringLiteral(""));
    shap->addChild(shapChild);
    pict->addChild(shap);

    return pict;
}

void DocxInsertImagePrivate::setLoadImgCount(int count)
{
    m_loadImgCount = count;
}

DocxMediaFile * DocxInsertImagePrivate::mediafileInfo(const QString &imgName)
{
    DocxMediaFile *mediaFile =  new DocxMediaFile(imgName);
    DocxMediaFile *img = findImg(mediaFile);
    QString strId;
    if (!img) {
        QString strRelactionType = QStringLiteral("/image");
        m_imgs.append(mediaFile);
        mediaFile->setName(QString("image%1.%2")
                           .arg(m_imgs.size() + m_loadImgCount).arg(mediaFile->suffix()));
        // get save Id
        m_doc->m_documentShips.addDocumentRelationship(strRelactionType, QString("media/%1")
                                                            .arg(mediaFile->name()), strId);

        mediaFile->setId(strId);
        if (!m_doc->m_contentTypes.isContentKey(mediaFile->suffix()))
            m_doc->m_contentTypes.addDefault(mediaFile->suffix(), mediaFile->mimeType());
    } else {
        delete mediaFile;
        mediaFile = img;
    }
    return mediaFile;
}

DocxMediaFile *DocxInsertImagePrivate::findImg(const DocxMediaFile *media) const
{
    for (DocxMediaFile *element : m_imgs) {
        if (element->hashKey() == media->hashKey())
            return element;
    }
    return nullptr;
}

TagElement *DocxInsertImagePrivate::shapetypeStyle()
{
    TagElement *styleElement = new TagElement(QStringLiteral("v:shapetype"));
    styleElement->addProperty(QStringLiteral("id"), QStringLiteral("_x0000_t75"));
    styleElement->addProperty(QStringLiteral("coordsize"), QStringLiteral("21600,21600"));
    styleElement->addProperty(QStringLiteral("o:spt"), QStringLiteral("75"));
    styleElement->addProperty(QStringLiteral("o:preferrelative"), QStringLiteral("t"));
    styleElement->addProperty(QStringLiteral("path"), QStringLiteral("m@4@5l@4@11@9@11@9@5xe"));
    styleElement->addProperty(QStringLiteral("filled"), QStringLiteral("f"));
    styleElement->addProperty(QStringLiteral("stroked"), QStringLiteral("f"));

    TagElement *child = new TagElement(QStringLiteral("v:stroke"));
    child->addProperty(QStringLiteral("joinstyle"), QStringLiteral("miter"));
    styleElement->addChild(child);

    // v:formulas
    child = new TagElement(QStringLiteral("v:formulas"));
    TagElement *formulasChild = new TagElement(QStringLiteral("v:f"));
    formulasChild->addProperty(QStringLiteral("eqn"), QStringLiteral("if lineDrawn pixelLineWidth 0"));
    child->addChild(formulasChild);

    formulasChild = new TagElement(QStringLiteral("v:f"));
    formulasChild->addProperty(QStringLiteral("eqn"), QStringLiteral("sum @0 1 0"));
    child->addChild(formulasChild);

    formulasChild = new TagElement(QStringLiteral("v:f"));
    formulasChild->addProperty(QStringLiteral("eqn"), QStringLiteral("sum 0 0 @1"));
    child->addChild(formulasChild);

    formulasChild = new TagElement(QStringLiteral("v:f"));
    formulasChild->addProperty(QStringLiteral("eqn"), QStringLiteral("prod @2 1 2"));
    child->addChild(formulasChild);

    formulasChild = new TagElement(QStringLiteral("v:f"));
    formulasChild->addProperty(QStringLiteral("eqn"), QStringLiteral("prod @3 21600 pixelWidth"));
    child->addChild(formulasChild);

    formulasChild = new TagElement(QStringLiteral("v:f"));
    formulasChild->addProperty(QStringLiteral("eqn"), QStringLiteral("prod @3 21600 pixelHeight"));
    child->addChild(formulasChild);

    formulasChild = new TagElement(QStringLiteral("v:f"));
    formulasChild->addProperty(QStringLiteral("eqn"), QStringLiteral("sum @0 0 1"));
    child->addChild(formulasChild);

    formulasChild = new TagElement(QStringLiteral("v:f"));
    formulasChild->addProperty(QStringLiteral("eqn"), QStringLiteral("prod @6 1 2"));
    child->addChild(formulasChild);

    formulasChild = new TagElement(QStringLiteral("v:f"));
    formulasChild->addProperty(QStringLiteral("eqn"), QStringLiteral("prod @7 21600 pixelWidth"));
    child->addChild(formulasChild);

    formulasChild = new TagElement(QStringLiteral("v:f"));
    formulasChild->addProperty(QStringLiteral("eqn"), QStringLiteral("sum @8 21600 0"));
    child->addChild(formulasChild);

    formulasChild = new TagElement(QStringLiteral("v:f"));
    formulasChild->addProperty(QStringLiteral("eqn"), QStringLiteral("prod @7 21600 pixelHeight"));
    child->addChild(formulasChild);

    formulasChild = new TagElement(QStringLiteral("v:f"));
    formulasChild->addProperty(QStringLiteral("eqn"), QStringLiteral("sum @10 21600 0"));
    child->addChild(formulasChild);

    styleElement->addChild(child);
    // end v:formulas


    child = new TagElement(QStringLiteral("v:path"));
    child->addProperty(QStringLiteral("o:extrusionok"), QStringLiteral("f"));
    child->addProperty(QStringLiteral("gradientshapeok"), QStringLiteral("t"));
    child->addProperty(QStringLiteral("o:connecttype"), QStringLiteral("rect"));
    styleElement->addChild(child);

    child = new TagElement(QStringLiteral("o:lock"));
    child->addProperty(QStringLiteral("v:ext"), QStringLiteral("edit"));
    child->addProperty(QStringLiteral("aspectratio"), QStringLiteral("t"));
    styleElement->addChild(child);


    return styleElement;
}

const DocxMediaFile *DocxInsertImagePrivate::media(const QByteArray hashkey)
{
    for (const DocxMediaFile *element : m_imgs) {
        if (element->hashKey() == hashkey)
            return element;
    }
    return nullptr;
}

QVector<DocxMediaFile *> DocxInsertImagePrivate::imgs() const
{
    return m_imgs;
}

DocxInsertImagePrivate::~DocxInsertImagePrivate()
{
    if (!m_imgs.isEmpty()) {
        qDeleteAll(m_imgs);
        m_imgs.clear();
    }
}

}
