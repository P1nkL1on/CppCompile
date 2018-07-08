#include "waiter.h"

using namespace LCompile;
using namespace Utils;
#include "valuetypes.h"

void Waiter::parse(const QStringList &buffer)
{
    int lineIndex = 0;
    int prevCandCount = -1;
    ValueType lastVT, VT;
    for (const QString line0 : buffer){
        QString line = line0;
        ++lineIndex;
        trace(QString("Now parsing line №%1: \"%2\"").arg(lineIndex).arg(line), messageType::information);
        QString nowParseCandidate;
        ValueTypesHolder vth;
        vth.setDefaultTypes();
        for (int i = 0; i < line.length(); ++i){
            nowParseCandidate += line[i];
            int candCount = -1;
            VT = vth.detectType(nowParseCandidate, candCount);
            if (candCount > 1 || (candCount == 1 && (VT.toString() == "[none]")))
                trace(QString("%3) Candidate count: %1 in [%2]")
                      .arg(candCount).arg(nowParseCandidate).arg(lineIndex));
            else
                if (candCount == 1)
                    trace(QString("%3) This can be only %1 in [%2]")
                          .arg(VT.toString()).arg(nowParseCandidate).arg(lineIndex));
            if (candCount == 0){
                // if previous was a 1 and now 0
                if (prevCandCount == 1)
                {
                    line = line.mid(i);
                    i = -1;
                    nowParseCandidate.clear();
                    trace(QString("%3) Was parsed exactly %1; Trimming a line; Now parsing a line [%2]")
                          .arg(lastVT.toString()).arg(line).arg(lineIndex));
                }
                else
                    break;
            }
            // exact checking
            prevCandCount = candCount;
            lastVT = VT;
        }
    }
}
