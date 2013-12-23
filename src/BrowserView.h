#ifndef BROWSERVIEW_H
#define BROWSERVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include "qtmozembed/qgraphicsmozview.h"

class BrowserView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit BrowserView (const QString& url, QWidget* parent = 0);
    QGraphicsMozView* GetMozView(void);
public Q_SLOTS:
    void onInitialized();
    void onRequestGLContext(bool& hasContext, QSize& viewPortSize);
    void load(const QString& url);
protected:
    void resizeEvent(QResizeEvent *event);

private:
    QGraphicsScene mScene;
    QGraphicsMozView mMozView;
    QString mStartURL;
};

#endif //BrowserView_H
