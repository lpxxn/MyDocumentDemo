#ifndef DOCXZIPWRITER_H
#define DOCXZIPWRITER_H

#include <QString>
class QIODevice;
class QZipWriter;
namespace TDocx
{
class DocxZipWriter
{
public:
    explicit DocxZipWriter(const QString &filePath);
    explicit DocxZipWriter(QIODevice* device);

    ~DocxZipWriter();

    void addFile(const QString &filePath, QIODevice *device);
    void addFile(const QString &filePath, const QByteArray &data);
    bool error() const;
    void close();

private:
    QZipWriter* m_writer;
};
}

#endif // DOCXZIPWRITER_H
