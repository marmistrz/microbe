#include "SettingsDialog.h"
#include <QPushButton>

SettingsDialog::SettingsDialog(QWidget *parent) :
    AbstractDialog(parent)
{
    mainLayout = new QVBoxLayout;

    searchEngineButton = new QMaemo5ValueButton("Selected search engine");
    mainLayout->addWidget(searchEngineButton);

    setLayout(mainLayout);
}

SettingsDialog::on_MozContext_recvObserve(const QString message, const QVariant data)
{
    if (message == "embed:prefs")
    {
        //TODO what now?
    }
}
