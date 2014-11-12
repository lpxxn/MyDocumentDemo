#include "comdatafun.h"

#include <QTime>
#include <QCryptographicHash>
#include <QBuffer>

namespace TDocx
{
ComDataFun::ComDataFun()
{
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
}

QString ComDataFun::hexNumber(int count)
{    
    QString hexStr;
    while(count--) {
        int value = qrand() % 15;
        hexStr += QString::number(value, 16).toUpper();
    }
    return hexStr;
}

QByteArray ComDataFun::byteHash(const QByteArray &bytes)
{
    return QCryptographicHash::hash(bytes, QCryptographicHash::Md5);
}

QByteArray ComDataFun::imageHash(const QImage &img)
{
    QByteArray ba;
    QBuffer buffer(&ba);
    buffer.open(QIODevice::WriteOnly);
    img.save(&buffer);
    return QCryptographicHash::hash(ba, QCryptographicHash::Md5);
}
}
