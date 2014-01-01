#include "SettingsDialog.h"
#include <QPushButton>

SettingsDialog::SettingsDialog(QWidget *parent) :
    AbstractDialog(parent)
{
    QVBoxLayout * mainLayout = new QVBoxLayout;
    mainLayout->addWidget(new QPushButton(this));
    mainLayout->addWidget(new QPushButton(this));
    mainLayout->addWidget(new QPushButton(this));

    setLayout(mainLayout);
}
