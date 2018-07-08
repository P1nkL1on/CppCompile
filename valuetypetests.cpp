#include "valuetypetests.h"


LCompile::ValueTypesHolder LCompile::ValueTypeTests::defaultHolder() const
{
    ValueTypesHolder vth;
    vth.setDefaultTypes();
    return vth;
}

QString LCompile::ValueTypeTests::getType(const LCompile::ValueTypesHolder &holder, const QString &line) const
{
    return holder.detectType(line).toString();
}
QString LCompile::ValueTypeTests::getType(const LCompile::ValueTypesHolder &holder, int &variantCount, const QString &line) const
{
    return holder.detectType(line, variantCount).toString();
}

void LCompile::ValueTypeTests::testDetectType01()
{
    QCOMPARE(getType(defaultHolder(), ""), ValueType().toString());
}

void LCompile::ValueTypeTests::testDetectType02()
{
    QCOMPARE(getType(defaultHolder(), "int"), ValueType().basicInt().toString());
}

void LCompile::ValueTypeTests::testDetectType03()
{
    QCOMPARE(getType(defaultHolder(), "  float "), ValueType().basicFloat().toString());
}

void LCompile::ValueTypeTests::testDetectType04()
{
    QCOMPARE(getType(defaultHolder(), " vo i d"), ValueType().toString());
}

void LCompile::ValueTypeTests::testDetectType05()
{
    QCOMPARE(getType(defaultHolder(), "       void     "), ValueType().basicVoid().toString());
}

void LCompile::ValueTypeTests::testDetectType06()
{
    QCOMPARE(getType(defaultHolder(), "   floAt   "), ValueType().toString());
}

void LCompile::ValueTypeTests::testPointer01()
{
    QString line = "  float**  ";
    int level = defaultHolder().trimPointers(line, '*');
    QCOMPARE(level, 2);
    QCOMPARE(line, QString("float"));
}

void LCompile::ValueTypeTests::testPointer02()
{
    QString line = "int";
    int level = defaultHolder().trimPointers(line, '*');
    QCOMPARE(level, 0);
    QCOMPARE(line, QString("int"));
}

void LCompile::ValueTypeTests::testPointer03()
{
    QString line = "    T YP  ER    ";
    int level = defaultHolder().trimPointers(line, '*');
    QCOMPARE(level, 0);
    QCOMPARE(line, QString("T YP  ER"));
}

void LCompile::ValueTypeTests::testPointer04()
{
    QString line = "   void *  ***    ";
    int level = defaultHolder().trimPointers(line, '*');
    QCOMPARE(level, 4);
    QCOMPARE(line, QString("void"));
}

void LCompile::ValueTypeTests::testPointer05()
{
    QString line = "** double **";
    int level = defaultHolder().trimPointers(line, '*');
    QCOMPARE(level, 2);
    QCOMPARE(line, QString("** double"));
}

void LCompile::ValueTypeTests::testPointer06()
{
    QString line = "    int   *    *    *   *    *    *";
    int level = defaultHolder().trimPointers(line, '*');
    QCOMPARE(level, 6);
    QCOMPARE(line, QString("int"));
}

void LCompile::ValueTypeTests::testPointer07()
{
    QString line = "  *  v  *  void *  *  i ** **";
    int level = defaultHolder().trimPointers(line, '*');
    QCOMPARE(level, 4);
    QCOMPARE(line, QString("*  v  *  void *  *  i"));
}

void LCompile::ValueTypeTests::testComplex01()
{
    QCOMPARE(getType(defaultHolder(), "   Void ***   "), ValueType().toString());
}

void LCompile::ValueTypeTests::testComplex02()
{
    const auto vRes = ValueType("float", 5);
    QCOMPARE(getType(defaultHolder(), "  float  *  * ***  "), vRes.toString());
}

void LCompile::ValueTypeTests::testComplex03()
{
    QCOMPARE(getType(defaultHolder(), "  ** int * int ** "), ValueType().toString());
}

void LCompile::ValueTypeTests::testVariants01()
{
    int count = -1;
    QString res =getType(defaultHolder(), count, " flo");
    QCOMPARE(count, 1);
    QCOMPARE(res, ValueType().toString());
}

void LCompile::ValueTypeTests::testVariants02()
{
    int count = -1;
    ValueTypesHolder vht = defaultHolder();
    vht.addValueType(ValueType("floooat"));
    vht.addValueType(ValueType("flot"));
    vht.addValueType(ValueType("floooAt"));
    QString res =getType(vht, count, " flo");
    QCOMPARE(count, 4);
    QCOMPARE(res, ValueType().toString());
}

void LCompile::ValueTypeTests::testVariants03()
{
    int count = -1;
    QString res = getType(defaultHolder(), count, " vo * *");
    QCOMPARE(count, 0);
    QCOMPARE(res, ValueType().toString());
}

void LCompile::ValueTypeTests::testVariants04()
{
    int count = -1;
    QString res =getType(defaultHolder(), count, "i");
    QCOMPARE(count, 1);
    QCOMPARE(res, ValueType().toString());
}

void LCompile::ValueTypeTests::testVariants05()
{
    int count = -1;
    QString res =getType(defaultHolder(), count, "  * * * i");
    QCOMPARE(count, 0);
    QCOMPARE(res, ValueType().toString());
}
