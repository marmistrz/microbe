#ifndef BOOKMARKSWINDOW_H
#define BOOKMARKSWINDOW_H

#include "StackedWindow.h"

class QAction;

class BookmarksWindow : public StackedWindow
{
    Q_OBJECT

public:
    explicit BookmarksWindow(QWidget *parent = 0);

public Q_SLOTS:

private Q_SLOTS:

private:
    void setLandscapeLayout();
    void setPortraitLayout();

private:
};

#endif // BOOKMARKSWINDOW_H
