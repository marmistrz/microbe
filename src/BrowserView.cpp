#include "BrowserView.h"
#include <QGLWidget>
#include <QDebug>

BrowserView::BrowserView(const QString& url, QWidget* parent) :
    QGraphicsView(parent),
    mStartURL(url)
{
    setViewport(new QGLWidget());
    //setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    
    setScene(&mScene);
    //mScene.setSceneRect(0,0,width(),height());
     
    setOptimizationFlags(QGraphicsView::DontSavePainterState);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFrameStyle(0);
    // These seem to give the best performance
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    mScene.setItemIndexMethod(QGraphicsScene::NoIndex);
    viewport()->setFocusPolicy(Qt::NoFocus);
    setFocusPolicy(Qt::StrongFocus);
    
    mScene.setStickyFocus(true); //### needed for correct focus handling

    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);
    setAttribute(Qt::WA_Maemo5NonComposited);
    
    viewport()->setAttribute(Qt::WA_OpaquePaintEvent);
    viewport()->setAttribute(Qt::WA_NoSystemBackground);
    viewport()->setAttribute(Qt::WA_Maemo5NonComposited);

    viewport()->setEnabled(true);
    setEnabled(true);
    
    //mScene.setSceneRect(0,0,width(),height());
    mScene.addItem(&mMozView);
    
    connect(&mMozView, SIGNAL(viewInitialized()), this, SLOT(onInitialized()));
    connect(&mMozView, SIGNAL(requestGLContextQGV(bool&,QSize&)), this, SLOT(onRequestGLContext(bool&,QSize&)));
    
    printf("Requested start page: %s\n", url.toUtf8().constData());
}

QGraphicsMozView* BrowserView::GetMozView(void)
{
    return &mMozView;
}

void BrowserView::onInitialized()
{
    mMozView.loadFrameScript("chrome://embedlite/content/embedhelper.js");
    mMozView.loadFrameScript("chrome://embedlite/content/SelectAsyncHelper.js");
    
    QStringList msglisteners;
    msglisteners << "embed:filepicker" << "embed:permissions" << "embed:select" << "embed:selectasync" \
        << "embed:login" << "embed:find" << "chrome:linkadded" << "embed:alert" << "embed:confirm" \
        << "embed:prompt" << "embed:auth" << "WebApps:PreInstall" << "WebApps:PostInstall" << "WebApps:Uninstall" \
        << "WebApps:Open" << "Content:ContextMenu" << "Content:SelectionRange" << "Content:SelectionCopied";
    mMozView.addMessageListeners(msglisteners);


    mMozView.load(mStartURL);
}

static bool viewHasGLContext(QGraphicsView* view)
{
    QGLWidget* qglwidget = qobject_cast<QGLWidget*>(view->viewport());
    if (qglwidget) {
        qglwidget->makeCurrent();
        QGLContext* context = const_cast<QGLContext*>(QGLContext::currentContext());
        if (context) {
            return true;
        }
    }
    return false;
}

void BrowserView::onRequestGLContext(bool& hasContext, QSize& viewPortSize)
{
    hasContext = false;
    if (!scene()) {
        return;
    }
            
    QList<QGraphicsView *> views = scene()->views();
    for (int i = 0; i < views.length(); ++i) {
        BrowserView *view = qobject_cast<BrowserView *>(views[i]);
        if (view && viewHasGLContext(view)) {
            const QGLContext* ctx = QGLContext::currentContext();
            if (ctx && ctx->device()) {
                //QRectF r(0, 0, ctx->device()->width(), ctx->device()->height());
                //printf("View: %i, %i, ctx: %f, %f\n", view->width(), view->height(), ctx->device()->width(), ctx->device()->height());
                //r = mapToScene(0, 0, ctx->device()->width(), ctx->device()->height());
                //r = mMozView.mapRectToScene(r);

                //printf("View: %i, %i, ctx: %i, %i\n", view->width(), view->height(), ctx->device()->width(), ctx->device()->height());
                //r = mapToScene(0, 0, ctx->device()->width(), ctx->device()->height());
                QPolygonF r = mapFromScene(0, 0, ctx->device()->width(), ctx->device()->height());
                viewPortSize = r.boundingRect().size().toSize();

                //viewPortSize = r.size().toSize();
            }
            hasContext = true;
            //qDebug("viewPortSize %i %i\n", viewPortSize.width(), viewPortSize.height());
            break;
        }
    }
}

// Testing only, not used at the moment.
void BrowserView::load(const QString& url)
{
    mMozView.load(url);
}

void BrowserView::resizeEvent(QResizeEvent *event)
{
//  Fixes resize issue but offsets clicks.
//    if (scene())
//        scene()->setSceneRect(QRect(QPoint(0, 0), event->size()));
    mMozView.resize(event->size());
    QGraphicsView::resizeEvent(event);
}


