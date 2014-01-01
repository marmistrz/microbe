#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include "dialogues/AbstractDialog.h"
#include <QBoxLayout>

class SettingsDialog : public AbstractDialog
{
    Q_OBJECT
public:
    explicit SettingsDialog(QWidget *parent = 0);
protected:
    QVBoxLayout * mainLayout;

};

#endif // SETTINGSDIALOG_H
