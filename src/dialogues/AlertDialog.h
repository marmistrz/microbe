#ifndef ALERTDIALOG_H
#define ALERTDIALOG_H

#include "AbstractDialog.h"

class QLabel;
class QPushButton;
class QDialogButtonBox;
class QGridLayout;

class AlertDialog : public AbstractDialog
{
    Q_OBJECT

public:
    explicit AlertDialog(const QString& title, const QString& message, QWidget *parent = 0);

private:
    void setLandscapeLayout();
    void setPortraitLayout();

private:
    QDialogButtonBox* mButtonBox;
    QLabel* mMessage;
    QPushButton* mOkButton;
    QGridLayout* mGrid;
};

#endif // ALERTDIALOG_H
