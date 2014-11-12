#include "docxmediafile.h"
#include "comdatafun.h"

#include <QBuffer>
#include <QMimeType>
#include <QMimeDatabase>

namespace TDocx
{
DocxMediaFile::DocxMediaFile(const QString &imageName)
{
    QImage img(imageName);

    QBuffer buffer(&m_content);
    buffer.open(QIODevice::WriteOnly);
    img.save(&buffer);
    m_hashKey = ComDataFun::byteHash(m_content);

    QMimeDatabase database;
    QMimeType type = database.mimeTypeForFile(imageName);
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

DocxMediaFile::DocxMediaFile()
{

}

}
