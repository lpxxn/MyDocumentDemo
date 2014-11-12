#ifndef DOCXLISTFORMAT_H
#define DOCXLISTFORMAT_H
#include "docx_global.h"
#include "itagelement.h"
#include "docxfont.h"

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

class DOCX_EXPORT DocxListFormat
{
public:
    DocxListFormat();
    DocxListFormat(const ListFormatStyle &listStyle);    

    virtual ~DocxListFormat();

    DocxFont font() const;
    void setFont(const DocxFont &font);

    ListFormatStyle flag() const;
    void setFlag(const ListFormatStyle &flag);

private:
    ListFormatStyle m_flag = ListFormatStyle::None;

    DocxFont m_font;

};

}

#endif // DOCXLISTFORMAT_H
