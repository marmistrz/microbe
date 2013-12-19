#ifndef NAVIGATIONTOOLBAR_H
#define NAVIGATIONTOOLBAR_H

#include "Enums.h"
#include <QToolBar>

class BrowserView;

class NavigationToolBar : public QToolBar
{
    Q_OBJECT

public:
    explicit NavigationToolBar(BrowserView* view, QWidget *parent = 0);
    ~NavigationToolBar() {}
    void setLandscapeLayout();
    void setPortraitLayout();

public Q_SLOTS:
    void onLoadingChanged();
    void onNavigationHistoryChanged();

private:
    QAction *m_historyAction;
    QAction *m_addBookmarkAction;
    QAction *m_addressAction;
    QAction *m_stopAction;
    QAction *m_fullScreenAction;
};

#endif // NAVIGATIONTOOLBAR_H
