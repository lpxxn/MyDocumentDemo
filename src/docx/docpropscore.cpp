#include "docpropscore.h"

namespace TDocx
{

docPropsCore::docPropsCore(CreateFlag flag)
    : AbstractOOXmlFile(flag)
{
}


void docPropsCore::saveToXmlFile(QIODevice *device) const
{
}

bool docPropsCore::loadFromXmlFile(QIODevice *device)
{
    return true;
}


}


