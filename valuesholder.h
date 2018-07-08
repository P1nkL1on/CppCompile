#ifndef VALUESHOLDER_H
#define VALUESHOLDER_H

#include "valuetypes.h"

namespace LCompile{

class ValueToken{
private:
    ValueType m_type;
    QString m_value;
};

class ValuesHolder
{
public:
    ValuesHolder() = default;
private:
    QVector<ValueToken> m_tokens;
};

}

#endif // VALUESHOLDER_H
