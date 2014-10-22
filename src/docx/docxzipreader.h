#ifndef DOCXZIPREADER_H
#define DOCXZIPREADER_H
#include "docx_global.h"
#include <QScopedPointer>
#include <QStringList>

class QZipReader;
class QIODevice;

namespace TDocx
{
class DOCX_EXPORT DocxZipReader
{
public:
    explicit DocxZipReader(const QString &fileName);
    explicit DocxZipReader(QIODevice *device);

    ~DocxZipReader();

    bool exists() const;
    QStringList filePaths() const;
    QByteArray fileData(const QString &fileName) const;

private:
    void init();
    QScopedPointer<QZipReader> m_reader;
    QStringList m_filePaths;
};
}

#endif // DOCXZIPREADER_H
