#include "Settings.h"
#include <QDir>
#include <QDesktopServices>

Settings* settingsInstance = 0;

Settings::Settings(QObject *parent) :
    QSettings(QString("Microbe"), QString("Microbe"), parent),
    m_language("en"),
    m_orientation(ScreenOrientation::Automatic)
{
    if (!settingsInstance) {
        settingsInstance = this;
    }
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
        m_language = lang;
        Q_EMIT languageChanged(lang);
    }
}

void Settings::setScreenOrientation(ScreenOrientation::Orientation orientation) {
    if (orientation != this->screenOrientation()) {
        m_orientation = orientation;
        Q_EMIT screenOrientationChanged(orientation);
    }
}

