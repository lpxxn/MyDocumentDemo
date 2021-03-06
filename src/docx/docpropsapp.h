#ifndef DOCPROPSAPP_H
#define DOCPROPSAPP_H
#include "docx_global.h"
#include "abstractooxmlfile.h"

#include <QMap>

namespace TDocx
{
class DOCX_EXPORT DocPropsApp : public AbstractOOXmlFile
{
public:
    DocPropsApp(CreateFlag flag);

    void initDefaultProperties();

    void addProperty(const QString &name, const QString &value);
    void modifyProperty(const QString &key, const QString &value);

    void modifyTemplate(const QString &value);
    void modifyTotalTime(const QString &value);
    void modifyPages(const QString &value);
    void modifyWords(const QString &value);
    void modifyCharacters(const QString &value);

    void saveToXmlFile(QIODevice *device) const;
    bool loadFromXmlFile(QIODevice *device);

private:
    QMap<QString, QString> m_properties;
};
}
#endif // DOCPROPSAPP_H
