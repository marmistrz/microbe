#ifndef BROWSERWINDOW_H
#define BROWSERWINDOW_H

#include "StackedWindow.h"

class QAction;
class BrowserView;
class NavigationToolBar;

class BrowserWindow : public StackedWindow
{
    Q_OBJECT

public:
    explicit BrowserWindow(const QString& url = "about:blank", QWidget *parent = 0);

public Q_SLOTS:
    void toggleFullScreen();

private Q_SLOTS:
    void showSettingsDialog();
    void showAboutDialog();
    void showAddBookmarkDialog();
    void showBookmarksWindow();
    void showHistory();
    void stopLoading();

private:
    void setLandscapeLayout();
    void setPortraitLayout();

private:
    QAction *m_settingsAction;
    QAction *m_aboutAction;
    QAction *m_fullScreenAction;
    BrowserView *mBrowserView;
    NavigationToolBar *mNavigationBar;
    bool m_fullscreen;
};

#endif // BROWSERWINDOW_H
