#ifndef DOCPROPSCORE_H
#define DOCPROPSCORE_H
#include "docx_global.h"
#include "abstractooxmlfile.h"


namespace TDocx
{
class DOCX_EXPORT docPropsCore : public AbstractOOXmlFile
{
public:
    docPropsCore(CreateFlag flag);

    void saveToXmlFile(QIODevice *device) const;
    bool loadFromXmlFile(QIODevice *device);
};
}

#endif // DOCPROPSCORE_H
