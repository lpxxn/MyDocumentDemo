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
    void saveToXmlFile(QIODevice *device) const;
    bool loadFromXmlFile(QIODevice *device);
    QString currentRsid() const { return m_currentRisids; }
    void initTags();

private:
    ITagElement* m_rsids;
    QString m_currentRisids;
    QVector<ITagElement*> m_wTags;

};
}

#endif // DOCXSETTINGS_H
