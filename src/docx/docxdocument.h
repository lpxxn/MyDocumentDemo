#ifndef DOCXDOCUMENT_H
#define DOCXDOCUMENT_H
#include "docx_global.h"
#include "abstractooxmlfile.h"
#include <QString>
namespace TDocx
{
class DOCX_EXPORT DocxDocument : public AbstractOOXmlFile
{
public:
    DocxDocument(CreateFlag flag);
    void saveToXmlFile(QIODevice *device) const;
    bool loadFromXmlFile(QIODevice *device);

};
}
#endif // DOCXDOCUMENT_H
