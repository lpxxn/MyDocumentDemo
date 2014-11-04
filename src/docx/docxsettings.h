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
    QString currentRsid() const { return m_currentRisids; }
    void initTags();
    QString currentRisids() const { return m_currentRisids; }
    QString defaultRsids() const { return m_defaultRsids; }

private:
    TagElement* m_rsids;
    QString m_defaultRsids;
    QString m_currentRisids;
    QVector<TagElement*> m_wTags;

};
}

#endif // DOCXSETTINGS_H
