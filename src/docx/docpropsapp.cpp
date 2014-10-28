#include "docpropsapp.h"


namespace TDocx
{
docPropsApp::docPropsApp(CreateFlag flag)
    : AbstractOOXmlFile(flag)
{
}

void docPropsApp::saveToXmlFile(QIODevice *device) const
{
}

bool docPropsApp::loadFromXmlFile(QIODevice *device)
{
    return true;
}


}


