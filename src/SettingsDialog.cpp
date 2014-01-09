#include "SettingsDialog.h"
#include <QDebug>

SettingsDialog::SettingsDialog(QWidget *parent) :
    AbstractDialog(parent)
{
    m_settings = Settings::instance();

    mainLayout = new QVBoxLayout;

    searchEngineButton = new QMaemo5ValueButton("Selected search engine");
    mainLayout->addWidget(searchEngineButton);

    searchEngineButton->setValueText(m_settings->searchEngine());

    setLayout(mainLayout);
}
