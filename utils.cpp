#include "utils.h"

void Utils::trimString(QString &string)
{
    string = string.trimmed();
}

void Utils::trace(const QString &message, const Utils::messageType &type)
{
    if (type >= 0)
        qDebug() << QString("%1%2")
                    .arg(messageHeaders[type]).arg(message);
}

QString Utils::joinStrings(const QVector<QString> &words,
        const QString &separate,
        const QString &prev,
        const QString &post)
{
    QString res = "";
    for (int i = 0; i < words.length(); ++i)
    {
        bool isLast = (i == words.length() - 1);
        res += prev + words[i] + post + ((isLast)? "" : separate);
    }
    return res;
}
