#include "docxzipreader.h"
#include <private/qzipreader_p.h>
#include <QDebug>

namespace TDocx
{
DocxZipReader::DocxZipReader(const QString &filePath) :
    m_reader(new QZipReader(filePath))
{
    init();
}

DocxZipReader::DocxZipReader(QIODevice *device) :
        m_reader(new QZipReader(device))
{
    init();
}

DocxZipReader::~DocxZipReader()
{

}


bool DocxZipReader::exists() const
{
    return m_reader->exists();
}

QStringList DocxZipReader::filePaths() const
{
    return m_filePaths;
}

QByteArray DocxZipReader::fileData(const QString &fileName) const
{
    return m_reader->fileData(fileName);
}

/*!
 * \brief 读取路径
 */
void DocxZipReader::init()
{
    QList<QZipReader::FileInfo> allFiles = m_reader->fileInfoList();
    foreach (const QZipReader::FileInfo &fi, allFiles) {
        if (fi.isFile) {
            qDebug() << fi.filePath;
            m_filePaths.append(fi.filePath);
        }
    }
}

}
