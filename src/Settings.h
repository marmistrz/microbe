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
    
    inline signed int memoryCacheSize() const { return -1; } /*FIXME*/
    inline QString language() const { return mLanguage; }
    inline ScreenOrientation::Orientation screenOrientation() const { return mOrientation; }

    static Settings* instance();
public Q_SLOTS:
    void saveSettings();
    void restoreSettings();
    void setLanguage(const QString &lang);
    void setScreenOrientation(ScreenOrientation::Orientation orientation);
    void onRecvObserve(const QString message, const QVariant data);
    void setSearchEngine(const QString engine) {/*FIXME*/}
    QString searchEngine() const {return mSearchEngine;}

private:

private Q_SLOTS:

Q_SIGNALS:
    void languageChanged(const QString &language);
    void screenOrientationChanged(ScreenOrientation::Orientation orientation);

protected:
    QMozContext * MozContext;

private:
    QString mLanguage;
    ScreenOrientation::Orientation mOrientation;
    QString mSearchEngine;
    QStringList m_availableSearchEngines;
};

#endif // SETTINGS_H
