#include "AbstractDialog.h"
#include <QApplication>
#include <QDesktopWidget>

AbstractDialog::AbstractDialog(QWidget *parent) :
    QDialog(parent),
    m_portrait(false)
{
    this->setAttribute(Qt::WA_DeleteOnClose, true);
    this->connect(QApplication::desktop(), SIGNAL(resized(int)), this, SLOT(onOrientationChanged()));
}

void AbstractDialog::onOrientationChanged() {
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

