#include "SettingsDialog.h"

#include "LanguageSelector.h"
#include "MemoryCacheSizeSelector.h"
#include "ScreenOrientationSelector.h"

#include <QBoxLayout>
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QLabel>
#include <QMaemo5ValueButton>
#include <QPushButton>

#include <QDebug>

SettingsDialog::SettingsDialog(QWidget *parent) :
    AbstractDialog(parent),
    mButtonBox(new QDialogButtonBox(Qt::Vertical, this)),
    mSaveButton(mButtonBox->addButton(tr("Save"), QDialogButtonBox::ActionRole)),
    mMainLayout(new QVBoxLayout()), // Not sure here
    mGrid(new QGridLayout(this))
{
    // Window Setup
    this->setWindowTitle(tr("Settings"));
    mSettings = Settings::instance();

    // Add settings
    mMainLayout->addWidget(new QLabel(tr("Browser"), this), 0, Qt::AlignHCenter);
    
    mLanguageSelector = new LanguageSelector(tr("Language"), true, this);
    mMainLayout->addWidget(mLanguageSelector);
    
    mMemoryCacheSizeSelector = new MemoryCacheSizeSelector(tr("Memory cache size"), this);
    mMainLayout->addWidget(mMemoryCacheSizeSelector);
    
    mOrientationSelector = new ScreenOrientationSelector(tr("Screen orientation"), this);
    mMainLayout->addWidget(mOrientationSelector);
    
    searchEngineButton = new QMaemo5ValueButton("Selected search engine");
    mMainLayout->addWidget(searchEngineButton);

    this->loadSettings();
    this->onOrientationChanged();
}

void SettingsDialog::setLandscapeLayout() {
    this->setMaximumHeight(260);
    mButtonBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    if (mGrid->isEmpty()) {
        mGrid->addLayout(mMainLayout, 0, 0);
        mGrid->addWidget(mButtonBox, 0, 1, Qt::AlignBottom);
    }
    else {
        mGrid->removeWidget(mButtonBox);
        mGrid->addWidget(mButtonBox, 0, 1, Qt::AlignBottom);
    }
}

void SettingsDialog::setPortraitLayout() {
    this->setMaximumHeight(400);
    mButtonBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    if (mGrid->isEmpty()) {
        mGrid->addLayout(mMainLayout, 0, 0);
        mGrid->addWidget(mButtonBox, 1, 0);
    }
    else {
        mGrid->removeWidget(mButtonBox);
        mGrid->addWidget(mButtonBox, 1, 0);
    }
}

void SettingsDialog::loadSettings()
{
    mLanguageSelector->setValue(mSettings->language());
    mMemoryCacheSizeSelector->setValue(mSettings->memoryCacheSize());
    mOrientationSelector->setValue(mSettings->screenOrientation());
       
    searchEngineButton->setValueText(mSettings->searchEngine());
}
