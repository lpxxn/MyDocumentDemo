#ifndef CONTENTTYPES_H
#define CONTENTTYPES_H
#include "docx_global.h"
#include "abstractooxmlfile.h"

#include <QString>
#include <QMap>

namespace TDocx
{

class DOCX_EXPORT ContentTypes : public AbstractOOXmlFile
{
public:
    ContentTypes(CreateFlag flag);

    virtual ~ContentTypes();

    void addDefault(const QString &key, const QString &value);
    void addDocumentOverride(const QString &key, const QString &value);
    bool isContentKey(const QString &key);
    void addOverrideDefault();
    QMap<QString, QString> contentFiles();

    void saveToXmlFile(QIODevice *device) const;
    bool loadFromXmlFile(QIODevice *device);


private:
    void addOverride(const QString &key, const QString &value);
    QMap<QString, QString> m_defaults;
    QMap<QString, QString> m_overrides;
    QString m_package_prefix;
    QString m_document_prefix;
    QString m_msword_prefix;

};
}

#endif // CONTENTTYPES_H
