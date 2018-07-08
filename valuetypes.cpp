#include "valuetypes.h"

using namespace LCompile;
using namespace Utils;

QString ValueType::string() const
{
    return m_string;
}

QString ValueType::toString() const
{
    if (isNone())
        return "[none]";
    return QString("[%1%2]").arg(string()).arg(pointerLevelStars());
}

ValueType ValueType::basicVoid()
{
    return ValueType("void");
}

ValueType ValueType::basicInt()
{
    return ValueType("int");
}

ValueType ValueType::basicFloat()
{
    return ValueType("float");
}

bool ValueType::isNone() const
{
    return m_isNone;
}

int ValueType::pointerLevel() const
{
    return m_pointerLevel;
}

QString ValueType::pointerLevelStars() const
{
    return QString().leftJustified(m_pointerLevel, '*');
}

ValueType ValueType::pointerToIt() const
{
    return ValueType(m_string, m_pointerLevel + 1);
}

bool ValueType::isPointer() const
{
    return m_pointerLevel > 0;
}

ValueType ValueType::pointerToWhat() const
{
    if (isPointer())
        return ValueType(m_string, m_pointerLevel - 1);
    return ValueType();
}

void ValueTypesHolder::setDefaultTypes()
{
    m_types << ValueType::basicVoid() << ValueType::basicInt() << ValueType::basicFloat();
    m_basicTypesCount += 3;
}

ValueType ValueTypesHolder::detectType(const QString &line0) const
{
    int variantCount = 0;
    return detectType(line0, variantCount);
}

ValueType ValueTypesHolder::detectType(const QString &line0, int &variantCount) const
{
    QString line = line0;
    QStringList variants;
    QStringList correctWriteVariants;
    trimString(line);
    int pointerLevel = trimPointers(line, '*');
    for (const ValueType vt : m_types){
        // completely equal
        if (line == vt.string()){
            variantCount = 1;   // there is onl 1 correct variant
            return ValueType(vt, pointerLevel);
        }
        // completely equal, but mismatch
        if (line.toLower() == vt.string().toLower()){
            correctWriteVariants << vt.string();
            continue;
        }
        // the string is a start of type :      "flo" can be start of float
        // but only if this is not a "flo***"
        if (pointerLevel > 0)
            continue;
        // is a start of complete variant
        if (vt.string().indexOf(line) == 0)
            variants << vt.string();

    }
    if (variants.length() > 0){
        variantCount = variants.length();
        return ValueType();
    }
    if (correctWriteVariants.length())
        trace(QString("Unrecognised type <%1>. Did you mean any of: %2")
              .arg(line).arg(joinStrings(correctWriteVariants.toVector(),", ","<",">")),
              messageType::suggestion);
    variantCount = 0;
    return ValueType();
}

void ValueTypesHolder::addValueType(const ValueType &vt)
{
    m_types << vt;
}

int ValueTypesHolder::trimPointers(QString &line, const QChar &pointerSymbol) const
{
    if (!line.length())
        return 0;
    //   *  * *** 8asfasjf
    int resultCountLevel = 0;
    const QString availableSymbols = QString(pointerSymbol) + " ";
    for (int i = line.length() - 1; i >= 0; --i){
        auto c = line[i];
        if (c == pointerSymbol){
            ++resultCountLevel;
            continue;
        }
        if (availableSymbols.indexOf(c)<0){
            line = line.mid(0, i + 1);
            trimString(line);
            return resultCountLevel;
        }
    }
    trace(QString("Perhaps, string <%1> does not contain nothing, but symbols <%2>").arg(line).arg(availableSymbols));
    return -1;
}
