#include "abstractooxmlfileprivate.h"


namespace TDocx
{
AbstractOOXmlFilePrivate::AbstractOOXmlFilePrivate(AbstractOOXmlFile::CreateFlag flag)
    :relationships(new Relationships), flag(flag)
{

}


TDocx::AbstractOOXmlFilePrivate::~AbstractOOXmlFilePrivate()
{
    if (!relationships)
        delete relationships;
}

}
