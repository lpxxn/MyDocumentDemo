#include "abstractooxmlfile.h"
#include "abstractooxmlfileprivate.h"
#include "relationships.h"

#include <QByteArray>
#include <QBuffer>
#include <QString>

namespace TDocx
{
AbstractOOXmlFile::AbstractOOXmlFile(CreateFlag flag)
    : m_dprivate(new AbstractOOXmlFilePrivate(flag))
{

}

AbstractOOXmlFile::AbstractOOXmlFile(AbstractOOXmlFilePrivate* absprivate)
    : m_dprivate(absprivate)
{

}


AbstractOOXmlFile::~AbstractOOXmlFile()
{
    delete m_dprivate;
}

QByteArray AbstractOOXmlFile::saveToXmlData() const
{
    QByteArray data;
    QBuffer buffer(&data);
    buffer.open(QIODevice::WriteOnly);
    saveToXmlFile(&buffer);
    return data;
}

bool AbstractOOXmlFile::loadFromXmlData(const QByteArray &data)
{
    QBuffer buffer;
    buffer.setData(data);
    buffer.open(QIODevice::WriteOnly);

    return loadFromXmlFile(&buffer);
}

Relationships *AbstractOOXmlFile::relationships() const
{
    return this->m_dprivate->relationships;
}

void AbstractOOXmlFile::setFilePath(const QString &path)
{
    m_dprivate->filepathInPackage = path;
}

QString AbstractOOXmlFile::filePath() const
{
    return m_dprivate->filepathInPackage;
}

}
