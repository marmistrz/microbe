#ifndef STACKEDWINDOW_H
#define STACKEDWINDOW_H

#include "Enums.h"
#include <QMainWindow>

class StackedWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StackedWindow(QWidget *parent = 0);
    ~StackedWindow() {}
    inline bool inPortrait() const { return m_portrait; }

protected Q_SLOTS:
    void setOrientation(ScreenOrientation::Orientation orientation);
    void onOrientationChanged();
    void toggleBusy(bool busy);

protected:
    inline virtual void setLandscapeLayout() {}
    inline virtual void setPortraitLayout() {}

private:
    bool m_portrait;
};

#endif // STACKEDWINDOW_H
