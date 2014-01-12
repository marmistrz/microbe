#include "MemoryCacheSizeSelector.h"
#include "SelectionModels.h"
#include <QMaemo5ListPickSelector>

MemoryCacheSizeSelector::MemoryCacheSizeSelector(const QString &text, QWidget *parent) :
    QMaemo5ValueButton(text, parent),
    mModel(new MemoryCacheSizeModel(this)),
    mSelector(new QMaemo5ListPickSelector(this))
{
    mSelector->setModel(mModel);
    mSelector->setModelColumn(0);
    this->setPickSelector(mSelector);
    this->connect(mSelector, SIGNAL(selected(QString)), this, SLOT(onSelected()));
}

void MemoryCacheSizeSelector::setValue(signed int value) {
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

signed int MemoryCacheSizeSelector::currentValue() {
    return mModel->value(mSelector->currentIndex()).toInt();
}

void MemoryCacheSizeSelector::onSelected() {
    Q_EMIT valueChanged(this->currentValue());
}
