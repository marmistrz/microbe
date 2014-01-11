#include "ConfirmationDialog.h"
#include <QLabel>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QDesktopServices>

#include <QDebug>

ConfirmationDialog::ConfirmationDialog(const QString& title, const QString& message, QWidget *parent) :
    AbstractDialog(parent),
    mButtonBox(new QDialogButtonBox(Qt::Vertical, this)),
    mMessage(new QLabel(message, this)),
    mOkButton(mButtonBox->addButton(tr("OK"), QDialogButtonBox::ActionRole)),
    mCancelButton(mButtonBox->addButton(tr("Cancel"), QDialogButtonBox::ActionRole)),
    mGrid(new QGridLayout(this))
{
    this->setWindowTitle(title);
    this->setModal(true);
    this->setWindowModality(Qt::WindowModal);
    
    mMessage->setText(message);
    mMessage->setWordWrap(true);
    
    mOkButton->setDefault();
    this->connect(mOkButton, SIGNAL(clicked()), this, SLOT(accept()));
    this->connect(mCancelButton, SIGNAL(clicked()), this, SLOT(reject()));

    this->onOrientationChanged();
}

void ConfirmationDialog::setLandscapeLayout() {
    this->setMaximumHeight(260);
    mButtonBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    if (mGrid->isEmpty()) {
        mGrid->addWidget(mMessage, 0, 0, Qt::AlignHCenter);
        mGrid->addWidget(mButtonBox, 0, 1, Qt::AlignBottom);
    }
    else {
        mGrid->setAlignment(mMessage, Qt::AlignHCenter);
        mGrid->removeWidget(mButtonBox);
        mGrid->addWidget(mButtonBox, 0, 1, Qt::AlignBottom);
    }
}

void ConfirmationDialog::setPortraitLayout() {
    this->setMaximumHeight(400);
    mButtonBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    if (mGrid->isEmpty()) {
        mGrid->addWidget(mMessage, 0, 0, Qt::AlignHCenter);
        mGrid->addWidget(mButtonBox, 1, 0);
    }
    else {
        mGrid->setAlignment(mMessage, Qt::AlignHCenter);
        mGrid->removeWidget(mButtonBox);
        mGrid->addWidget(mButtonBox, 1, 0);
    }
}
