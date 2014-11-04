#ifndef DOCXSTYLEEFFECTS_H
#define DOCXSTYLEEFFECTS_H
#include "docx_global.h"
#include "docxstyle.h"

namespace TDocx
{
class DOCX_EXPORT DocxStyleEffects : public DocxStyle
{
public:
    DocxStyleEffects(CreateFlag flag);

    void saveToXmlFile(QIODevice *device) const;
};
}

#endif // DOCXSTYLEEFFECTS_H
