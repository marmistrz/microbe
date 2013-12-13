#include "Utils.h"
#include <QDateTime>
#include <QFileInfo>
#include <QFile>

void Utils::log(const QString &filePath, const QByteArray &message) {
    QFile lf(filePath);

    if (lf.open(QIODevice::Append)) {
        lf.write(QDateTime::currentDateTime().toString().toUtf8() + ": " + message + "\n");
    }

    lf.close();
}

QString Utils::versionNumberString() {
    return QString("0.1");
}
