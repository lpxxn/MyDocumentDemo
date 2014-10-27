#ifndef ABSTRACTOOXMLFILEPRIVATE_H
#define ABSTRACTOOXMLFILEPRIVATE_H
#include "docx_global.h"
#include "relationships.h"
#include "abstractooxmlfile.h"
#include <QString>

namespace TDocx
{
class DOCX_EXPORT AbstractOOXmlFilePrivate
{
public:
    AbstractOOXmlFilePrivate(AbstractOOXmlFile::CreateFlag flag = AbstractOOXmlFile::CreateFlag::F_NewFromScratch);

    // save .xml as "word/document.xml"
    QString filepathInPackage;
    Relationships *relationships;
    AbstractOOXmlFile::CreateFlag flag;

    virtual ~AbstractOOXmlFilePrivate();



};
}

#endif // ABSTRACTOOXMLFILEPRIVATE_H
