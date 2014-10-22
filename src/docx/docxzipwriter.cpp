#include "docxzipwriter.h"

#include <private/qzipwriter_p.h>
#include <QDebug>

namespace TDocx
{

DocxZipWriter::DocxZipWriter(const QString &filePath)
{
    m_writer = new QZipWriter(filePath, QIODevice::WriteOnly);
    m_writer->setCompressionPolicy(QZipWriter::AutoCompress);

}

DocxZipWriter::DocxZipWriter(QIODevice* device)
{
    m_writer = new QZipWriter(device);
    m_writer->setCompressionPolicy(QZipWriter::AutoCompress);
}

DocxZipWriter::~DocxZipWriter()
{
    delete m_writer;
}

void DocxZipWriter::addFile(const QString &filePath, QIODevice *device)
{
    m_writer->addFile(filePath, device);
}

void DocxZipWriter::addFile(const QString &filePath, const QByteArray &data)
{
    m_writer->addFile(filePath, data);
}

bool DocxZipWriter::error() const
{
    return m_writer->status() != QZipWriter::NoError;
}

void DocxZipWriter::close()
{

}


}
