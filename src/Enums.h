#ifndef ENUMS_H
#define ENUMS_H

#include <QObject>

class ScreenOrientation : public QObject
{
    Q_OBJECT

    Q_ENUMS(Orientation)

public:
    enum Orientation {
        Automatic = 0,
        LockPortrait,
        LockLandscape
    };
};

#endif // ENUMS_H
