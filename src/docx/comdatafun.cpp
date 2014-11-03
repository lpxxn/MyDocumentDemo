#include "comdatafun.h"

#include <QTime>
ComDataFun::ComDataFun()
{
}

QString ComDataFun::hexNumber(int count)
{
    qsrand(QTime::currentTime().msec());
    QString hexStr;
    while(count--) {
        int value = qrand() % 15;
        hexStr += QString::number(value, 16).toUpper();
    }
    return hexStr;
}
