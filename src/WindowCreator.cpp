#include "WindowCreator.h"
#include "BrowserWindow.h"
#include <QGraphicsObject>
#include <QVariant>
#include <QGLWidget>
#include <QDebug>
#include <QTimer>
#include <QUrl>
#include "qtmozembed/qmozcontext.h"

MozWindowCreator::MozWindowCreator(const QString& aQmlstring, const bool& aGlwidget, const bool& aIsFullScreen)
{
    qmlstring = aQmlstring;
    glwidget = aGlwidget;
    mIsFullScreen = aIsFullScreen;
    
    if (!QMozContext::GetInstance()->initialized()) {
        connect(QMozContext::GetInstance(), SIGNAL(onInitialized()), this, SLOT(onInitialized()));
    } else {
        QTimer::singleShot(0, this, SLOT(onInitialized()));
    }
}

quint32
MozWindowCreator::newWindowRequested(const QString& url, const unsigned& aParentID, QNewWindowResponse* response)
{
    QUrl newUrl;
    if (!url.contains(QString("://")) && !url.startsWith(QString("about:"))) {
        newUrl = QUrl(QString("http://") + url);
    }
    else {
        newUrl = QUrl(url);
    }
/*    QString newHost = newUrl.host();
    if (newHost.startsWith(QString("www."))) {
        newHost = newHost.right(newHost.length() - 5);
    }
    QString newPath = newUrl.path();
    if (newPath.endsWith(QString("/"))) {
        newPath = newPath.left(newPath.length() - 1);
    }
    for (int i=0; i<mWindowStack.size(); i++) {
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
    if (response) {
        response->setNewWindowID(uniqueID);
    }
    return 0;
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
    BrowserWindow *view = new BrowserWindow;
    
/*    QUrl qml;
    if (qmlstring.isEmpty())

    // See NEMO#415 for an explanation of why this may be necessary.
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


void MozWindowCreator::onInitialized()
{
    qDebug("WindowCreator::onInitialized");
    QMozContext* context = QMozContext::GetInstance();
    context->setPref("extensions.logging.enabled", true);
    context->setPref("extensions.strictCompatibility",false);
    context->setPref("dom.experimental_forms", true);
    context->setPref("xpinstall.whitelist.add", "addons.mozilla.org");
    context->setPref("xpinstall.whitelist.add.180", "marketplace.firefox.com");
    context->setPref("security.alternate_certificate_error_page", "certerror");
    context->setPref("embedlite.azpc.handle.singletap", false);
    context->setPref("embedlite.azpc.json.singletap", true);
    context->setPref("embedlite.azpc.handle.longtap", false);
    context->setPref("embedlite.azpc.json.longtap", true);
    context->setPref("embedlite.azpc.json.viewport", true);
    context->setPref("embedlite.select.list.async", true);
    context->setPref("browser.ui.touch.left", 32);
    context->setPref("browser.ui.touch.right", 32);
    context->setPref("browser.ui.touch.top", 48);
    context->setPref("browser.ui.touch.bottom", 16);
    context->setPref("browser.ui.touch.weight.visited", 120);
    context->setPref("browser.download.folderList", 2); // 0 - Desktop, 1 - Downloads, 2 - Custom
    context->setPref("browser.download.useDownloadDir", false); // Invoke filepicker instead of immediate download to ~/Downloads
    context->setPref("browser.download.manager.retention", 2);
    context->setPref("browser.helperApps.deleteTempFileOnExit", false);
    context->setPref("browser.download.manager.quitBehavior", 1);
    context->setPref("keyword.enabled", true);
    
    QStringList observers;
    observers << "embed:download" << "embed:prefs" << "embed:allprefs" << "clipboard:setdata" << "embed:logger" << "embed:search";
    context->addObservers(observers);
}
