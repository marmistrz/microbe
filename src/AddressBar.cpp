#include "AddressBar.h"
#include <QDebug>
#include <QLineEdit>
#include "qtmozembed/qgraphicsmozview.h"

AddressBar::AddressBar(QWidget *parent) :
    QComboBox(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    setEditable(true);
    setInputMethodHints(Qt::ImhNoAutoUppercase | Qt::ImhNoPredictiveText);
    
    connect(this->lineEdit(), SIGNAL(returnPressed()), this, SLOT(onReturnPressed()));
}

void AddressBar::onLoadProgressChanged()
{
    QGraphicsMozView* view = qobject_cast<QGraphicsMozView*>(QObject::sender());
    if(view)
    {
        // Handle view->progress()
    }
}

void AddressBar::onURLChanged()
{
    QGraphicsMozView* view = qobject_cast<QGraphicsMozView*>(QObject::sender());
    if(view)
    {
        this->lineEdit()->setText(view->url().toEncoded());
        // For long, obscure URL's (SessionID, Hash etc) its easier to see what site we are on.
        this->lineEdit()->setCursorPosition(0);
    }
}

void AddressBar::onReturnPressed()
{
    printf("AddressBar::onReturnPressed: %s\n", this->lineEdit()->text().toUtf8().constData());
    Q_EMIT URLRequest(this->lineEdit()->text());
}
