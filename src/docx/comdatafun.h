#ifndef COMDATAFUN_H
#define COMDATAFUN_H

#include <QString>
#include <QByteArray>
#include <QImage>

namespace TDocx
{
const QString ridStr = QStringLiteral("rId");
const QString startMarkStr = QStringLiteral("tableStart");
const QString endMarkStr   = QStringLiteral("tableEnd");

class ComDataFun
{
public:
    ComDataFun();
    static QString hexNumber(int count = 8);
    static QByteArray imageHash(const QImage &img);
    static QByteArray byteHash(const QByteArray &bytes);
};
}

#endif // COMDATAFUN_H
