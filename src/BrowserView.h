#ifndef BROWSERVIEW_H
#define BROWSERVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include "qtmozembed/qgraphicsmozview.h"

class BrowserView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit BrowserView (QWidget* parent = 0);
public Q_SLOTS:
    void onInitialized();
    void onRequestGLContext(bool& hasContext, QSize& viewPortSize);
protected:
    void resizeEvent(QResizeEvent *event);

private:
    QGraphicsScene mScene;
    QGraphicsMozView mMozView;
};

#endif //BrowserView_H
