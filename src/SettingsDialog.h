#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QBoxLayout>
#include <QMaemo5ValueButton>

#include "dialogues/AbstractDialog.h"
#include "Settings.h"

class SettingsDialog : public AbstractDialog
{
    Q_OBJECT
public:
    explicit SettingsDialog(QWidget *parent = 0);
protected:
    QVBoxLayout * mainLayout;
    QMaemo5ValueButton * searchEngineButton;
    Settings * m_settings;

};

#endif // SETTINGSDIALOG_H
