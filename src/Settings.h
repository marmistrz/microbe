#ifndef SETTINGS_H
#define SETTINGS_H

#include "Enums.h"
#include <QSettings>
#include <QStringList>
#include <QSet>
#include <qplatformdefs.h>
#include "qtmozembed/qmozcontext.h"

class QNetworkProxy;
class QAuthenticator;

class Settings : public QSettings
{
    Q_OBJECT

    Q_PROPERTY(QString language
               READ language
               WRITE setLanguage
               NOTIFY languageChanged)
    Q_PROPERTY(ScreenOrientation::Orientation screenOrientation
               READ screenOrientation
               WRITE setScreenOrientation
               NOTIFY screenOrientationChanged)

    Q_PROPERTY(QString searchEngine READ searchEngine WRITE setSearchEngine) //NOTIFY searchEngineChanged)

public:
    explicit Settings(QObject *parent = 0);
    ~Settings();
    inline QString language() const { return m_language; }
    inline ScreenOrientation::Orientation screenOrientation() const { return m_orientation; }

    static Settings* instance();
public Q_SLOTS:
    void saveSettings();
    void restoreSettings();
    void setLanguage(const QString &lang);
    void setScreenOrientation(ScreenOrientation::Orientation orientation);
    void onRecvObserve(const QString message, const QVariant data);
    void setSearchEngine(const QString engine) {/*FIXME*/}
    QString searchEngine() const {return m_searchEngine;}

private:

private Q_SLOTS:

Q_SIGNALS:
    void languageChanged(const QString &language);
    void screenOrientationChanged(ScreenOrientation::Orientation orientation);

protected:
    QMozContext * MozContext;

private:
    QString m_language;
    ScreenOrientation::Orientation m_orientation;
    QString m_searchEngine;
};

#endif // SETTINGS_H
