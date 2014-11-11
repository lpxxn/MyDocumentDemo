#ifndef DOCXLISTFORMAT_H
#define DOCXLISTFORMAT_H
#include "docx_global.h"
#include "itagelement.h"

#include <QVector>
#include <QString>

namespace TDocx
{
enum class ListFormatStyle
{
    None = 0,
    Number = 1,
    Bullet = 2
};

class DOCX_EXPORT DocxListFormat : public ISaveToXml
{
public:
    DocxListFormat();
    DocxListFormat(const ListFormatStyle &listStyle);
    void saveToXmlElement(QXmlStreamWriter *writer) const;

    virtual ~DocxListFormat();

private:
    ListFormatStyle m_flag = ListFormatStyle::None;

};

}

#endif // DOCXLISTFORMAT_H
