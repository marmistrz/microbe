#ifndef ABSTRACTDIALOG_H
#define ABSTRACTDIALOG_H

#include <QDialog>

class QApplication;
class QDesktopWidget;

class AbstractDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AbstractDialog(QWidget *parent = 0);
    inline bool inPortrait() const { return m_portrait; }

protected Q_SLOTS:
    void onOrientationChanged();

protected:
    inline virtual void setLandscapeLayout() {}
    inline virtual void setPortraitLayout() {}

private:
    bool m_portrait;
};

#endif // ABSTRACTDIALOG_H
