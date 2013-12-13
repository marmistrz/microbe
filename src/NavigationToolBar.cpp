#include "NavigationToolBar.h"
#include "Settings.h"
#include <QAction>
#include <QComboBox>
#include <QToolBar>
#include <QToolButton>

NavigationToolBar::NavigationToolBar(QWidget *parent) :
    QToolBar(tr("Navigation Toolbar"), parent)
{
    this->setContextMenuPolicy(Qt::PreventContextMenu);

	m_historyAction = this->addAction(QIcon::fromTheme("browser_history"),QString::null, parent, SLOT(showHistory()));
	m_addBookmarkAction = this->addAction(QIcon::fromTheme("general_add"),QString::null, parent, SLOT(showAddBookmarkDialog()));

    QComboBox* empty = new QComboBox(this);
    empty->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    empty->setEditable(true);
	m_addressAction = this->addWidget(empty);

	m_stopAction = this->addAction(QIcon::fromTheme("general_stop"),QString::null, parent, SLOT(stopLoading()));
	m_stopAction->setVisible(false);

    this->addAction(QIcon::fromTheme("general_mybookmarks_folder"),QString::null, parent, SLOT(showBookmarksWindow()));

    m_fullScreenAction = this->addAction(QIcon::fromTheme("general_fullsize"),QString::null, parent, SLOT(toggleFullScreen()));

}

void NavigationToolBar::setLandscapeLayout() {
    m_addressAction->setVisible(true);
}

void NavigationToolBar::setPortraitLayout() {
    m_addressAction->setVisible(false);
}
