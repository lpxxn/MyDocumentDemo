#ifndef DOCXFONTTABLE_H
#define DOCXFONTTABLE_H
#include "docx_global.h"
#include "abstractooxmlfile.h"
#include <QString>
#include <QPair>
#include <QVector>
#include <QMap>
#include <QXmlStreamWriter>

namespace TDocx
{
struct fontInfo
{
    typedef QPair<QString, QString> pairValue;
    QString name;
    QVector<pairValue> values;
    void addProperty(QString name, QString value) {
        values.append(pairValue(name, value));
    }
};

class DOCX_EXPORT docxfontTable : public AbstractOOXmlFile
{
public:
    docxfontTable(CreateFlag flag);

    void saveToXmlFile(QIODevice *device) const;
    bool loadFromXmlFile(QIODevice *device);

    void saveFonts(QXmlStreamWriter &writer) const;
    void initFonts();
private:
    QMap<QString, QVector<fontInfo> > m_fonts;

};
}

#endif // DOCXFONTTABLE_H
