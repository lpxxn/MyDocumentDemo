#ifndef DOCXSETTINGS_H
#define DOCXSETTINGS_H
#include "itagelement.h"
#include "docx_global.h"
#include "abstractooxmlfile.h"

#include <QVector>

namespace TDocx
{
class DOCX_EXPORT DocxSettings : public AbstractOOXmlFile
{
public:
    DocxSettings(CreateFlag flag);
    virtual ~DocxSettings();
    void saveToXmlFile(QIODevice *device) const;
    bool loadFromXmlFile(QIODevice *device);    


private:
    void initTags();
    QVector<TagElement*> m_wTags;

};
}

#endif // DOCXSETTINGS_H
