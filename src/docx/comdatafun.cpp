#include "comdatafun.h"

#include <QTime>
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
