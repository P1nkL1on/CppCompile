#ifndef WAITER_H
#define WAITER_H
#include "utils.h"

namespace LCompile{

enum AwaitType{
    none = -1,
    endlineSymbol = 0,      // \n
    endOperatorSymbol = 1,  // ;
    valueType = 10,         // int float, etc
};

class Waiter
{
public:
    Waiter() = default;
    void parse(const QStringList &buffer);
private:
//    QVector<QVector<AwaitType>> m_currentlyAwaits;
};

}

#endif // WAITER_H
