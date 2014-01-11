#include "ScreenOrientationSelector.h"
#include "SelectionModels.h"
#include <QMaemo5ListPickSelector>

ScreenOrientationSelector::ScreenOrientationSelector(const QString &text, QWidget *parent) :
    QMaemo5ValueButton(text, parent),
    mModel(new ScreenOrientationModel(this)),
    mSelector(new QMaemo5ListPickSelector(this))
{
    mSelector->setModel(mModel);
    mSelector->setModelColumn(0);
    this->setPickSelector(mSelector);
    this->connect(mSelector, SIGNAL(selected(QString)), this, SLOT(onSelected()));
}

void ScreenOrientationSelector::setValue(ScreenOrientation::Orientation value) {
    bool found = false;
    int i = 0;

    while ((!found) && (i < mModel->rowCount())) {
        found = static_cast<ScreenOrientation::Orientation>(mModel->value(i).toInt()) == value;

        if (found) {
            mSelector->setCurrentIndex(i);
        }

        i++;
    }

    if (!found) {
        mSelector->setCurrentIndex(0);
    }
}

ScreenOrientation::Orientation ScreenOrientationSelector::currentValue() {
    return static_cast<ScreenOrientation::Orientation>(mModel->value(mSelector->currentIndex()).toInt());
}

void ScreenOrientationSelector::onSelected() {
    emit valueChanged(this->currentValue());
}
