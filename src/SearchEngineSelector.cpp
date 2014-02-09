#include "SearchEngineSelector.h"
#include "SelectionModels.h"
#include <QMaemo5ListPickSelector>

SearchEngineSelector::SearchEngineSelector(const QString &text, QWidget *parent) :
    QMaemo5ValueButton(text, parent),
    mModel(new SearchEngineModel(this)),
    mSelector(new QMaemo5ListPickSelector(this))
{
    mSelector->setModel(mModel);
    mSelector->setModelColumn(0);
    this->setPickSelector(mSelector);
    this->connect(mSelector, SIGNAL(selected(QString)), this, SLOT(onSelected()));
}

void SearchEngineSelector::setValue(signed int value) {
    bool found = false;
    int i = 0;

    while ((!found) && (i < mModel->rowCount())) {
        found = mModel->value(i).toInt() == value;

        if (found) {
            mSelector->setCurrentIndex(i);
        }

        i++;
    }

    if (!found) {
        mSelector->setCurrentIndex(0);
    }
}

signed int SearchEngineSelector::currentValue() {
    return mModel->value(mSelector->currentIndex()).toInt();
}

void SearchEngineSelector::onSelected() {
    Q_EMIT valueChanged(this->currentValue());
}
