#ifndef DOCXNUMBERING_H
#define DOCXNUMBERING_H

#include "docx_global.h"
#include "abstractooxmlfile.h"

#include <QByteArray>

namespace TDocx
{
class DOCX_EXPORT DocxNumbering : public AbstractOOXmlFile
{
public:
    DocxNumbering(CreateFlag flag);

    void saveToXmlFile(QIODevice *device) const;
    bool loadFromXmlFile(QIODevice *device);

private:
    QByteArray m_data;
};
}

#endif // DOCXNUMBERING_H
