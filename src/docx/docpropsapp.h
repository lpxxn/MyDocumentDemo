#ifndef DOCPROPSAPP_H
#define DOCPROPSAPP_H
#include "docx_global.h"
#include "abstractooxmlfile.h"

namespace TDocx
{
class DOCX_EXPORT docPropsApp : public AbstractOOXmlFile
{
public:
    docPropsApp(CreateFlag flag);

    void saveToXmlFile(QIODevice *device) const;
    bool loadFromXmlFile(QIODevice *device);
};
}
#endif // DOCPROPSAPP_H
