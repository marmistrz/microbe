#include "StackedWindow.h"
#include "Settings.h"
//#include "../base/windowstack.h"
#include <QApplication>
#include <QDesktopWidget>

StackedWindow::StackedWindow(QWidget *parent) :
    QMainWindow(parent),
    m_portrait(false)
{
    this->setAttribute(Qt::WA_Maemo5StackedWindow, true);
    this->setAttribute(Qt::WA_DeleteOnClose, true);
    this->setOrientation(Settings::instance()->screenOrientation());

    //WindowStack::instance()->addWindowToStack(this);

    this->connect(Settings::instance(), SIGNAL(screenOrientationChanged(ScreenOrientation::Orientation)), this, SLOT(setOrientation(ScreenOrientation::Orientation)));
    this->connect(QApplication::desktop(), SIGNAL(resized(int)), this, SLOT(onOrientationChanged()));
}

void StackedWindow::setOrientation(ScreenOrientation::Orientation orientation) {
    switch (orientation) {
    case ScreenOrientation::Automatic:
        this->setAttribute(Qt::WA_Maemo5AutoOrientation, true);
        break;
    case ScreenOrientation::LockPortrait:
        this->setAttribute(Qt::WA_Maemo5PortraitOrientation, true);
        break;
    case ScreenOrientation::LockLandscape:
        this->setAttribute(Qt::WA_Maemo5LandscapeOrientation, true);
        break;
    default:
        this->setAttribute(Qt::WA_Maemo5LandscapeOrientation, true);
    }
}

void StackedWindow::onOrientationChanged() {
    QRect screen = QApplication::desktop()->screenGeometry();

    if (screen.width() > screen.height()) {
        m_portrait = false;
        this->setLandscapeLayout();
    }
    else {
        m_portrait = true;
        this->setPortraitLayout();
    }
}

void StackedWindow::toggleBusy(bool busy) {
    this->setAttribute(Qt::WA_Maemo5ShowProgressIndicator, busy);
}
