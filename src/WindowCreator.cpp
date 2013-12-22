#include "WindowCreator.h"
#include "BrowserWindow.h"
#include <QGraphicsObject>
#include <QVariant>
#include <QGLWidget>
#include <QUrl>
#include "qtmozembed/qmozcontext.h"

MozWindowCreator::MozWindowCreator(const QString& aQmlstring, const bool& aGlwidget, const bool& aIsFullScreen)
{
    qmlstring = aQmlstring;
    glwidget = aGlwidget;
    mIsFullScreen = aIsFullScreen;
}

quint32
MozWindowCreator::createView(const QString &url, const quint32 &aParentID)
{
    QUrl newUrl;
    if (!url.contains(QString("://")) && !url.startsWith(QString("about:"))) {
        newUrl = QUrl(QString("http://") + url);
    }
    else {
        newUrl = QUrl(url);
    }
    QString newHost = newUrl.host();
    if (newHost.startsWith(QString("www."))) {
        newHost = newHost.right(newHost.length() - 5);
    }
    QString newPath = newUrl.path();
    if (newPath.endsWith(QString("/"))) {
        newPath = newPath.left(newPath.length() - 1);
    }
/*    for (int i=0; i<mWindowStack.size(); i++) {
        QDeclarativeView* view = mWindowStack.at(i);
        QObject* item = view->rootObject()->findChild<QObject*>("mainScope");
        QDeclarativeMozView* mozview = item->findChild<QDeclarativeMozView*>("webViewport");
        if (mozview) {
            QGraphicsMozView* gmozview = mozview->findChild<QGraphicsMozView*>("QGraphicsMozView");
            QUrl pageUrl = gmozview ? gmozview->url() : QUrl();
            QString pageHost = pageUrl.host();
            if (pageHost.startsWith(QString("www."))) {
                pageHost = pageHost.right(newHost.length() - 5);
            }
            QString pagePath = pageUrl.path();
            if (pagePath.endsWith(QString("/"))) {
                pagePath = pagePath.left(pagePath.length() - 1);
            }
            if (pageHost == newHost && pagePath == newPath) {
                if (mIsFullScreen)
                    view->showFullScreen();
                else
                    view->show();
                return 0;
            }
        }
    }
*/
    quint32 uniqueID = 0;
    BrowserWindow* view = CreateNewWindow(url, &uniqueID, aParentID);
    mWindowStack.append(view);
    if (mIsFullScreen)
        view->showFullScreen();
    else
        view->show();
    return uniqueID;
}

void
MozWindowCreator::bringToFront()
{
    BrowserWindow* view = mWindowStack.at(0);
    if (!view)
        return;

    if (mIsFullScreen)
        view->showFullScreen();
    else
        view->show();
}

BrowserWindow*
MozWindowCreator::CreateNewWindow(const QString& url, quint32 *aUniqueID, quint32 aParentID)
{
    BrowserWindow *view = new BrowserWindow(url);
    
/*  // See NEMO#415 for an explanation of why this may be necessary.
    if (glwidget && !getenv("SWRENDER"))
        view->setViewport(new QGLWidget);
    else {
        qDebug() << "Not using QGLWidget viewport";
        QMozContext::GetInstance()->setIsAccelerated(false);
    }
*/
/*    view->engine()->setOfflineStoragePath(QString("%1/.mozilla/").arg(QDir::homePath()));
    view->rootContext()->setContextProperty("startURL", QVariant(url));
    view->rootContext()->setContextProperty("createParentID", QVariant(aParentID));
    view->rootContext()->setContextProperty("QmlHelperTools", new QmlHelperTools(this));
    view->rootContext()->setContextProperty("MozContext", QMozContext::GetInstance());
    view->rootContext()->setContextProperty("QGVWindow", view);
    view->setSource(qml);
    QObject* item = view->rootObject()->findChild<QObject*>("mainScope");
    if (item) {
        QObject::connect(item, SIGNAL(pageTitleChanged(QString)), view, SLOT(setWindowTitle(QString)));
    }

    if (aUniqueID) {
        QDeclarativeMozView* mozview = item->findChild<QDeclarativeMozView*>("webViewport");
        if (mozview)
            *aUniqueID = mozview->uniqueID();
    }

*/
    return view;
}
