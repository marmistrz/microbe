#ifndef WINDOWCREATOR_H
#define WINDOWCREATOR_H
#include "BrowserWindow.h"
#include "qtmozembed/qmozviewcreator.h"

class MozWindowCreator : public QMozViewCreator
{
public:
    MozWindowCreator(const QString& aQmlstring, const bool& aGlwidget, const bool& aIsFullScreen);
    BrowserWindow* CreateNewWindow(const QString& url = QString("about:blank"), quint32* aUniqueID = 0, quint32 aParentID = 0);
    virtual quint32 createView(const QString& url, const quint32& aParentID);
    void bringToFront();

public:
    QList<BrowserWindow*> mWindowStack;
private:
    QString qmlstring;
    bool glwidget;
    bool mIsFullScreen;
};
#endif // WINDOWCREATOR_H
