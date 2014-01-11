#ifndef CONFIRMATIONDIALOG_H
#define CONFIRMATIONDIALOG_H

#include "AbstractDialog.h"

class QLabel;
class QPushButton;
class QDialogButtonBox;
class QGridLayout;

class ConfirmationDialog : public AbstractDialog
{
    Q_OBJECT

public:
    explicit ConfirmationDialog(const QString& title, const QString& message, QWidget *parent = 0);

private:
    void setLandscapeLayout();
    void setPortraitLayout();

private:
    QDialogButtonBox* mButtonBox;
    QLabel* mMessage;
    QPushButton* mOkButton;
    QPushButton* mCancelButton;
    QGridLayout* mGrid;
};

#endif // CONFIRMATIONDIALOG_H
