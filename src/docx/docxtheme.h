#ifndef DOCXTHEME_H
#define DOCXTHEME_H

#include "docx_global.h"
#include "abstractooxmlfile.h"

#include <QByteArray>

namespace TDocx
{
class DOCX_EXPORT docxTheme : public AbstractOOXmlFile
{
public:
    docxTheme(CreateFlag flag);

    void saveToXmlFile(QIODevice *device) const;
    bool loadFromXmlFile(QIODevice *device);

private:
    QByteArray m_data;

};
}

#endif // DOCXTHEME_H
