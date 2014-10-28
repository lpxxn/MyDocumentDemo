#ifndef DOCPROPSAPP_H
#define DOCPROPSAPP_H
#include "docx_global.h"
#include "abstractooxmlfile.h"

#include <QMap>

namespace TDocx
{
class DOCX_EXPORT docPropsApp : public AbstractOOXmlFile
{
public:
    docPropsApp(CreateFlag flag);

    void initDefaultProperties();

    void addProperty(const QString &name, const QString &value);
    void modifyProperty(const QString &key, const QString &value);

    void modifyTemplate(const QString &value);
    void modifyTotalTime(const QString &value);
    void modifyPages(const QString &value);
    void modifyWords(const QString &vlaue);
    void modifyCharacters(const QString &vlaue);

    void saveToXmlFile(QIODevice *device) const;
    bool loadFromXmlFile(QIODevice *device);

private:
    QMap<QString, QString> m_properties;
};
}
#endif // DOCPROPSAPP_H
