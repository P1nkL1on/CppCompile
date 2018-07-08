#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QVector>
#include <QDebug>

namespace Utils {
    enum messageType{
        none = -1,
        information = 0,
        warning = 1,
        suggestion = 2
    };
    const QVector<QString> messageHeaders = {"INFO:  ", "WARN:  ", "SGST:  "};

    void trace(const QString &message, const messageType &type = messageType::information);
    void trimString(QString &string);
    QString joinStrings(const QVector<QString> &words,
                        const QString &separate = ", ",
                        const QString &prev = "",
                        const QString &post = "");
}
#endif // UTILS_H
