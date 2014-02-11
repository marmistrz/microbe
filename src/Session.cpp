#include "Session.h"
#include "qtmozembed/qmozcontext.h"
#include "Settings.h"
//#include "notifications.h"
//#include "transfermanager.h"
//#include "thumbnailcache.h"
#ifdef Q_WS_MAEMO_5
//#include "windowstack.h"
#endif
#include <QDebug>
#include <QNetworkConfigurationManager>
#include <QNetworkAccessManager>
#include <QTimer>
#include <QVariantMap>

Session* sessionInstance = 0;

Session::Session(QObject *parent) :
    QObject(parent),
    m_ncm(new QNetworkConfigurationManager(this)),
    m_nam(new QNetworkAccessManager(this)),
    m_settings(new Settings(this)),
    m_context(QMozContext::GetInstance())
//    m_notifications(new Notifications(this)),
//    m_transferManager(new TransferManager(this)),
//    m_cache(new ThumbnailCache)
  #ifdef Q_WS_MAEMO_5
//    m_stack(new WindowStack(this))
  #endif
{
    if (!sessionInstance) {
        sessionInstance = this;
    }

//    this->connect(m_transferManager, SIGNAL(alert(QString)), m_notifications, SLOT(onAlert(QString)));
//    m_transferManager->setNetworkAccessManager(this->networkAccessManager());
    m_settings->restoreSettings();
//    m_transferManager->restoreStoredDownloads();

    if (!QMozContext::GetInstance()->initialized()) {
        connect(QMozContext::GetInstance(), SIGNAL(onInitialized()), this, SLOT(onInitialized()));
    } else {
        QTimer::singleShot(0, this, SLOT(onInitialized()));
    }    
}

Session::~Session() {
//    delete m_cache;
//    m_cache = 0;
}

Session* Session::instance() {
    return sessionInstance;
}

void Session::onInitialized()
{
    qDebug("Session::onInitialized");
    m_context->setPref("extensions.logging.enabled", true);
    m_context->setPref("extensions.strictCompatibility",false);
    m_context->setPref("dom.experimental_forms", true);
    m_context->setPref("xpinstall.whitelist.add", "addons.mozilla.org");
    m_context->setPref("xpinstall.whitelist.add.180", "marketplace.firefox.com");
    m_context->setPref("security.alternate_certificate_error_page", "certerror");
    m_context->setPref("embedlite.azpc.handle.singletap", false);
    m_context->setPref("embedlite.azpc.json.singletap", true);
    m_context->setPref("embedlite.azpc.handle.longtap", false);
    m_context->setPref("embedlite.azpc.json.longtap", true);
    m_context->setPref("embedlite.azpc.json.viewport", true);
    m_context->setPref("embedlite.select.list.async", true);
    m_context->setPref("browser.ui.touch.left", 32);
    m_context->setPref("browser.ui.touch.right", 32);
    m_context->setPref("browser.ui.touch.top", 48);
    m_context->setPref("browser.ui.touch.bottom", 16);
    m_context->setPref("browser.ui.touch.weight.visited", 120);
    m_context->setPref("browser.download.folderList", 2); // 0 - Desktop, 1 - Downloads, 2 - Custom
    m_context->setPref("browser.download.useDownloadDir", false); // Invoke filepicker instead of immediate download to ~/Downloads
    m_context->setPref("browser.download.manager.retention", 2);
    m_context->setPref("browser.helperApps.deleteTempFileOnExit", false);
    m_context->setPref("browser.download.manager.quitBehavior", 1);
    m_context->setPref("keyword.enabled", true);
    // Params being tested:
    //m_context->setPref("layers.progressive-paint", false);
    
    QStringList observers;
    observers << "embed:download" << "embed:prefs" << "embed:allprefs" << "clipboard:setdata" << "embed:logger" << "embed:search";
    m_context->addObservers(observers);
    
    qDebug("Adding search plugins");
    QVariantMap message;
    message.insert("msg", "loadxml");
    message.insert("uri", "chrome://embedlite/content/bing.xml");
    message.insert("confirm", false);
    m_context->sendObserve("embedui:search", message);
    message["uri"] = "chrome://embedlite/content/google.xml";
    m_context->sendObserve("embedui:search", message);
    message["uri"] = "chrome://embedlite/content/yahoo.xml";
    m_context->sendObserve("embedui:search", message);
    
}

