#ifndef UTILS_H
#define UTILS_H

#include "Enums.h"
#include <QString>

class Utils
{

public:
    static void log(const QString &filePath, const QByteArray &message);
    static QString versionNumberString();
};

#endif // UTILS_H
