#include "SettingsDialog.h"
#include <QDebug>

SettingsDialog::SettingsDialog(QWidget *parent) :
    AbstractDialog(parent)
{
    MozContext = QMozContext::GetInstance();

    mainLayout = new QVBoxLayout;

    searchEngineButton = new QMaemo5ValueButton("Selected search engine");
    mainLayout->addWidget(searchEngineButton);

    setLayout(mainLayout);
}

void SettingsDialog::on_MozContext_recvObserve(const QString message, const QVariant data)
{
    QVariantMap qvmap = data.toMap(); // Convert the Json data to a map
    qDebug() << "==========================================================";
    qDebug() << qvmap;
    qDebug() << "==========================================================";
    if (message == "embed:prefs")
    {
        //TODO what now?
    }
}
