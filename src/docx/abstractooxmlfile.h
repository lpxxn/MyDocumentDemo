#ifndef ABSTRACTOOXMLFILE_H
#define ABSTRACTOOXMLFILE_H
#include "docx_global.h"

namespace TDocx
{
class DOCX_EXPORT AbstractOOXmlFile
{
public:
    enum class CreateFlag
    {
        F_NewFromScratch,
        F_LoadFromExists
    };

    virtual ~AbstractOOXmlFile();

protected:
    AbstractOOXmlFile(CreateFlag flag);
};
}

#endif // ABSTRACTOOXMLFILE_H
