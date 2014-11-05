#ifndef DOCXDOCUMENT_H
#define DOCXDOCUMENT_H
#include "docx_global.h"
#include "abstractooxmlfile.h"
#include "docxdocumentbuilder.h"
#include <QString>
namespace TDocx
{
class DOCX_EXPORT Document : public AbstractOOXmlFile
{
public:
    Document(CreateFlag flag);
    void saveToXmlFile(QIODevice *device) const;
    bool loadFromXmlFile(QIODevice *device);

private:
    friend class DocumentBuilder;

};
}
#endif // DOCXDOCUMENT_H
