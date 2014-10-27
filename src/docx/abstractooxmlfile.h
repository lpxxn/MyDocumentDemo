#ifndef ABSTRACTOOXMLFILE_H
#define ABSTRACTOOXMLFILE_H
#include "docx_global.h"

class QByteArray;
class QIODevice;

class QString;

namespace TDocx
{
class AbstractOOXmlFilePrivate;
class Relationships;

class DOCX_EXPORT AbstractOOXmlFile
{
public:
    enum class CreateFlag
    {
        F_NewFromScratch,
        F_LoadFromExists
    };

    virtual ~AbstractOOXmlFile();

    virtual QByteArray saveToXmlData() const;
    virtual bool loadFromXmlData(const QByteArray &data);

    virtual void saveToXmlFile(QIODevice *device) const = 0;
    virtual bool loadFromXmlFile(QIODevice *device) = 0;

    Relationships* relationships() const;
    void setFilePath(const QString &path);
    QString filePath() const;

protected:
    AbstractOOXmlFile(CreateFlag flag);
    AbstractOOXmlFile(AbstractOOXmlFilePrivate *absprivate);

private:
    AbstractOOXmlFilePrivate* m_dprivate;

};
}

#endif // ABSTRACTOOXMLFILE_H
