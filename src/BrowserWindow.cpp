#include "BrowserWindow.h"
#include "BookmarksWindow.h"
#include "BrowserView.h"
#include "NavigationToolBar.h"
//#include "aboutdialog.h"
//#include "settingsdialog.h"
//#include "../base/windowstack.h"
#include "Settings.h"
#include <QAction>
#include <QMenuBar>


#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGLWidget>
#include "qtmozembed/qgraphicsmozview.h"


BrowserWindow::BrowserWindow(QWidget *parent) :
    StackedWindow(parent),
    m_settingsAction(this->menuBar()->addAction(tr("Settings"), this, SLOT(showSettingsDialog()))),
    m_aboutAction(this->menuBar()->addAction(tr("About"), this, SLOT(showAboutDialog()))),
    m_fullscreen(false)
{    
    this->setWindowTitle("Microbe");
    //this->setAttribute(Qt::WA_DeleteOnClose, false);

    mNavigationBar = new NavigationToolBar(this);
    this->addToolBar(mNavigationBar);
    
    mBrowserView = new BrowserView(this);
    this->setCentralWidget(mBrowserView);    

    this->onOrientationChanged();
}

void BrowserWindow::setLandscapeLayout() {
    mNavigationBar->setLandscapeLayout();
}

void BrowserWindow::setPortraitLayout() {
    mNavigationBar->setPortraitLayout();
}

void BrowserWindow::showSettingsDialog() {
//    SettingsDialog *dialog = new SettingsDialog(this);
//    dialog->open();
}

void BrowserWindow::showAboutDialog() {
//    AboutDialog *dialog = new AboutDialog(this);
//    dialog->open();
}

void BrowserWindow::showAddBookmarkDialog() {
//    BookmarksWindow *window = new BookmarksWindow(this);
//    window->show();
}


void BrowserWindow::showBookmarksWindow() {
    BookmarksWindow *window = new BookmarksWindow(this);
    window->show();
}

void BrowserWindow::showHistory() {
//    BookmarksWindow *window = new BookmarksWindow(this);
//    window->show();
}

void BrowserWindow::stopLoading() {
//    BookmarksWindow *window = new BookmarksWindow(this);
//    window->show();
}



void BrowserWindow::toggleFullScreen() {
    if(!m_fullscreen)
    {
        this->showFullScreen();
        m_fullscreen = true;
    } else {
        this->showNormal();
        m_fullscreen = false;
    }    
}

