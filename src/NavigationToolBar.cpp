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
    this->setContextMenuPolicy(Qt::PreventContextMenu);

	m_historyAction = this->addAction(QIcon::fromTheme("browser_history"),QString::null, parent, SLOT(showHistory()));
	m_historyAction->setEnabled(false);
	
	m_addBookmarkAction = this->addAction(QIcon::fromTheme("general_add"),QString::null, parent, SLOT(showAddBookmarkDialog()));

    AddressBar* address = new AddressBar(this);
    m_addressAction = this->addWidget(address);

	m_stopAction = this->addAction(QIcon::fromTheme("general_stop"),QString::null, parent, SLOT(stopLoading()));
	m_stopAction->setVisible(false);

    this->addAction(QIcon::fromTheme("general_mybookmarks_folder"),QString::null, parent, SLOT(showBookmarksWindow()));

    m_fullScreenAction = this->addAction(QIcon::fromTheme("general_fullsize"),QString::null, parent, SLOT(toggleFullScreen()));
    
    QGraphicsMozView* moz = view->GetMozView();
    connect(address, SIGNAL(URLRequest(QString)), moz, SLOT(load(QString)));
    connect(moz, SIGNAL(urlChanged()), address, SLOT(onURLChanged()));

}

void NavigationToolBar::setLandscapeLayout() {
    m_addressAction->setVisible(true);
}

void NavigationToolBar::setPortraitLayout() {
    m_addressAction->setVisible(false);
}
