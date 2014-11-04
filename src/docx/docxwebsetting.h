#ifndef DOCXWEBSETTING_H
#define DOCXWEBSETTING_H

#include "docx_global.h"
#include "abstractooxmlfile.h"
#include <QVector>

namespace TDocx
{
class TagElement;

class DOCX_EXPORT DocxWebSetting : public AbstractOOXmlFile
{
public:
    DocxWebSetting(CreateFlag flag);

    virtual ~DocxWebSetting();

    void saveToXmlFile(QIODevice *device) const;
    bool loadFromXmlFile(QIODevice *device);

private:
    void initTag();
    QVector<TagElement*> m_tags;
};
}

#endif // DOCXWEBSETTING_H
