#include "BookmarksWindow.h"
#include "NavigationToolBar.h"
//#include "aboutdialog.h"
//#include "settingsdialog.h"
//#include "../base/windowstack.h"
#include "Settings.h"
#include <QAction>
#include <QMenuBar>

BookmarksWindow::BookmarksWindow(QWidget *parent) :
    StackedWindow(parent)
{    
    this->setWindowTitle("Bookmarks");

    this->onOrientationChanged();
}

void BookmarksWindow::setLandscapeLayout() {
}

void BookmarksWindow::setPortraitLayout() {
}

