#ifndef WINDOWCREATOR_H
#define WINDOWCREATOR_H
#include "BrowserWindow.h"

class QNewWindowResponse;
class MozWindowCreator : public QObject
{
    Q_OBJECT
public:
    MozWindowCreator(const QString& aQmlstring, const bool& aGlwidget, const bool& aIsFullScreen);
    BrowserWindow* CreateNewWindow(const QString& url = QString("about:blank"), quint32* aUniqueID = 0, quint32 aParentID = 0);
public Q_SLOTS:
    quint32 newWindowRequested(const QString& url, const unsigned& aParentID, QNewWindowResponse* response);
    void bringToFront();
    void onInitialized();

public:
    QList<BrowserWindow*> mWindowStack;
private:
    QString qmlstring;
    bool glwidget;
    bool mIsFullScreen;
};
#endif // WINDOWCREATOR_H
