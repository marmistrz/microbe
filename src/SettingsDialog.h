#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QBoxLayout>
#include <QMaemo5ValueButton>

#include "dialogues/AbstractDialog.h"
#include "qtmozembed/qmozcontext.h"

class SettingsDialog : public AbstractDialog
{
    Q_OBJECT
public:
    explicit SettingsDialog(QWidget *parent = 0);
protected:
    QVBoxLayout * mainLayout;
    QMaemo5ValueButton * searchEngineButton;
    QMozContext * MozContext;
public Q_SLOTS:
    void on_MozContext_recvObserve(const QString message, const QVariant data);

};

#endif // SETTINGSDIALOG_H
