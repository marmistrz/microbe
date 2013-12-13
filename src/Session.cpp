#include "Session.h"
#include "qtmozembed/qmozcontext.h"
#include "Settings.h"
//#include "notifications.h"
//#include "transfermanager.h"
//#include "thumbnailcache.h"
#ifdef Q_WS_MAEMO_5
//#include "windowstack.h"
#endif
#include <QNetworkConfigurationManager>
#include <QNetworkAccessManager>

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
    
}

Session::~Session() {
//    delete m_cache;
//    m_cache = 0;
}

Session* Session::instance() {
    return sessionInstance;
}

