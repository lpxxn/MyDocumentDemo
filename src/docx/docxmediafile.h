#ifndef DOCXMEDIAFILE_H
#define DOCXMEDIAFILE_H
#include "docx_global.h"
#include "itagelement.h"

#include <QString>
#include <QByteArray>
#include <QSize>

namespace TDocx
{
class DocxMediaFile
{
public:
    DocxMediaFile(const QString &imageName);

    QString suffix() const;

    QString mimeType() const;

    QByteArray content() const;

    QByteArray hashKey() const;
    QString name() const;
    void setName(const QString &name);

    QString Id() const;
    void setId(const QString &Id);

    QSize imgSize() const;
    void setImgSize(const QSize &imgSize);

private:
    QString m_Id;
    QString m_name;
    QString m_suffix;
    QString m_mimeType;
    QSize m_imgSize;
    QByteArray m_content;
    QByteArray m_hashKey;

};
// end DocxMediaFile

class AbstractDocument;
class DocxInsertImagePrivate
{
public:
    //DocxInsertImagePrivate(Document *doc);
    DocxInsertImagePrivate(AbstractDocument *doc);
    TagElement * imageTagElement(const QString &imgName, const QSize &size, bool firstImg = false);
    DocxMediaFile *findImg(const DocxMediaFile *media) const;
    QVector<DocxMediaFile *> imgs() const;

    virtual ~DocxInsertImagePrivate();

    DocxMediaFile *mediafileInfo(const QString &imgName);
    TagElement * imageTagElement(DocxMediaFile *mediaFile, const QSize &size, bool firstImg);
private:
    TagElement *shapetypeStyle();
    const DocxMediaFile* media(const QByteArray hashkey);

private:    
    AbstractDocument *m_doc;
    QVector<DocxMediaFile*> m_imgs;
};

}

#endif // DOCXMEDIAFILE_H
