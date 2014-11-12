#ifndef DOCXMEDIAFILE_H
#define DOCXMEDIAFILE_H
#include "docx_global.h"

#include <QString>
#include <QByteArray>

namespace TDocx
{
class DOCX_EXPORT DocxMediaFile
{
public:
    DocxMediaFile();
    DocxMediaFile(const QString &imageName);

    QString suffix() const;

    QString mimeType() const;

    QByteArray content() const;

    QByteArray hashKey() const;



private:
    QString m_suffix;
    QString m_mimeType;
    QByteArray m_content;
    QByteArray m_hashKey;

};
}

#endif // DOCXMEDIAFILE_H
