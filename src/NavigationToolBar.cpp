#include "NavigationToolBar.h"
#include "AddressBar.h"
#include "BrowserView.h"
#include "Settings.h"
#include <QAction>
#include <QToolBar>
#include <QToolButton>
#include "qtmozembed/qgraphicsmozview.h"

NavigationToolBar::NavigationToolBar(BrowserView* view, QWidget *parent) :
    QToolBar(tr("Navigation Toolbar"), parent)
{
    QGraphicsMozView* moz = view->GetMozView();
    
    this->setContextMenuPolicy(Qt::PreventContextMenu);

	m_historyAction = this->addAction(QIcon::fromTheme("browser_history"),QString::null, moz, SLOT(goBack()));
	m_historyAction->setEnabled(false);
	connect(moz, SIGNAL(navigationHistoryChanged()), this, SLOT(onNavigationHistoryChanged()));
	
	m_addBookmarkAction = this->addAction(QIcon::fromTheme("general_add"),QString::null, parent, SLOT(showAddBookmarkDialog()));

    AddressBar* address = new AddressBar(this);
    m_addressAction = this->addWidget(address);
    connect(address, SIGNAL(URLRequest(QString)), moz, SLOT(load(QString)));
    connect(moz, SIGNAL(urlChanged()), address, SLOT(onURLChanged()));

	m_stopAction = this->addAction(QIcon::fromTheme("general_stop"),QString::null, parent, SLOT(stopLoading()));
	m_stopAction->setVisible(false);

    this->addAction(QIcon::fromTheme("general_mybookmarks_folder"),QString::null, parent, SLOT(showBookmarksWindow()));

    m_fullScreenAction = this->addAction(QIcon::fromTheme("general_fullsize"),QString::null, parent, SLOT(toggleFullScreen()));
}

void NavigationToolBar::onNavigationHistoryChanged()
{
    QGraphicsMozView* view = qobject_cast<QGraphicsMozView*>(QObject::sender());
    if(view)
    {
        m_historyAction->setEnabled(view->canGoBack());
    }
}

void NavigationToolBar::setLandscapeLayout() {
    m_addressAction->setVisible(true);
}

void NavigationToolBar::setPortraitLayout() {
    m_addressAction->setVisible(false);
}
