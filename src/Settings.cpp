#include "Settings.h"
#include <QDir>
#include <QDesktopServices>
#include <QDebug>

Settings* settingsInstance = 0;

Settings::Settings(QObject *parent) :
    QSettings(QString("Microbe"), QString("Microbe"), parent),
    mLanguage("en"),
    mOrientation(ScreenOrientation::Automatic)
{
    if (!settingsInstance) {
        settingsInstance = this;
    }

    MozContext = QMozContext::GetInstance();
    connect(MozContext, SIGNAL(recvObserve(QString,QVariant)), this, SLOT(onRecvObserve(QString,QVariant)));
}

Settings::~Settings() {
    this->saveSettings();
}

Settings* Settings::instance() {
    return settingsInstance;
}

void Settings::restoreSettings() {
    this->beginGroup("System");
    this->setLanguage(this->value("language", QString("en")).toString());
    this->setScreenOrientation(static_cast<ScreenOrientation::Orientation>(this->value("screenOrientation", 0).toInt()));
    this->endGroup();
}

void Settings::saveSettings() {
    this->beginGroup("System");
    this->setValue("language", this->language());
    this->setValue("screenOrientation", ScreenOrientation::Orientation(this->screenOrientation()));
    this->endGroup();
}

void Settings::setLanguage(const QString &lang) {
    if (lang != this->language()) {
        mLanguage = lang;
        Q_EMIT languageChanged(lang);
    }
}

void Settings::setScreenOrientation(ScreenOrientation::Orientation orientation) {
    if (orientation != this->screenOrientation()) {
        mOrientation = orientation;
        Q_EMIT screenOrientationChanged(orientation);
    }
}

void Settings::onRecvObserve(const QString message, const QVariant data)
{
    QVariantMap datamap = data.toMap(); // Convert the Json data to a map
    qDebug() << "==========================================================";
    qDebug() << datamap;
    qDebug() << "==========================================================";
//    abort();
    if (message == "embed:prefs")
    {
        //TODO what now?
    }
    else if (message == "embed:search")
    {
        QString msg = datamap["msg"].toString();
        if (msg == "init")
        {
            QVariant engine = datamap["defaultEngine"];
            if (!engine.isNull())
            {
                mSearchEngine = engine.toString();
            }
        }
        else if (msg == "pluginslist")
        {
            // TODO what now?
        }

    }
}

