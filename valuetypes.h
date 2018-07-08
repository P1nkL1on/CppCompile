#ifndef VALUETYPES_H
#define VALUETYPES_H

#include "utils.h"

namespace LCompile{

class ValueType{
public:
    ValueType() = default;
    ValueType(const QString &string): m_string(string), m_isNone(false){
        if (string == "[none]")
        {
            int X = 10;
        }

    }
    ValueType(const QString &string, const int &pointerLevel):
        m_string(string), m_isNone(false), m_pointerLevel(pointerLevel){}
    ValueType(const ValueType &type, const int &pointerLevel):
        m_string(type.string()), m_isNone(false), m_pointerLevel(pointerLevel){}
    QString string() const;
    QString toString() const;
    static ValueType basicVoid();
    static ValueType basicInt();
    static ValueType basicFloat();
    bool isNone() const;
    int pointerLevel() const;
    QString pointerLevelStars() const;
    ValueType pointerToIt() const;
    bool isPointer() const;
    ValueType pointerToWhat() const;
private:
    QString m_string;
    bool m_isNone = true;
    int m_pointerLevel = 0;
};


class ValueTypesHolder
{
public:
    ValueTypesHolder() = default;
    void setDefaultTypes();
    ValueType detectType (const QString &line0) const;
    ValueType detectType(const QString &line0, int &variantCount) const;
    void addValueType(const ValueType &vt);
    int trimPointers(QString &line, const QChar &pointerSymbol) const;
private:
    QVector<ValueType> m_types;
    int m_basicTypesCount = 0;
};

}

#endif // VALUETYPES_H
