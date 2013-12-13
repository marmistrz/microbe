#ifndef DBUSADAPTOR_H
#define DBUSADAPTOR_H

#include <QObject>
#include <QDBusConnection>

class QNewWindowResponse;
class DBusAdaptor : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.mozilla.mozembed")

public:
    DBusAdaptor();

Q_SIGNALS:
    void newWindowUrl(QString url, unsigned dummy, QNewWindowResponse* newDummy);
    void bringToFront();

public Q_SLOTS:
    Q_SCRIPTABLE void newUrl(QString url);
    Q_SCRIPTABLE void show();
};

#endif //DBUSADAPTOR_H
