#ifndef VALUETYPETESTS_H
#define VALUETYPETESTS_H

#include <QTest>
#include "valuetypes.h"

namespace LCompile{
class ValueTypeTests : public QObject
{
    Q_OBJECT
public:

private:
    ValueTypesHolder defaultHolder() const;
    QString getType(const ValueTypesHolder &holder, const QString &line) const;
    QString getType(const ValueTypesHolder &holder, int &variantCount, const QString &line) const;
private slots:
    void testDetectType01();
    void testDetectType02();
    void testDetectType03();
    void testDetectType04();
    void testDetectType05();
    void testDetectType06();

    void testPointer01();
    void testPointer02();
    void testPointer03();
    void testPointer04();
    void testPointer05();
    void testPointer06();
    void testPointer07();

    void testComplex01();
    void testComplex02();
    void testComplex03();

    void testVariants01();
    void testVariants02();
    void testVariants03();
    void testVariants04();
    void testVariants05();
};
}
#endif // VALUETYPETESTS_H
