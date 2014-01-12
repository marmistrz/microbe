#include "LanguageSelector.h"
#include "SelectionModels.h"
#include <QMaemo5ListPickSelector>
#include <QDir>

LanguageSelector::LanguageSelector(const QString &text, bool hideUnavailable, QWidget *parent) :
    QMaemo5ValueButton(text, parent),
    mModel(new LanguageModel(this)),
    mSelector(new QMaemo5ListPickSelector(this))
{
    if (hideUnavailable) {
        hideUnavailableLanguages();
    }

    mSelector->setModel(mModel);
    mSelector->setModelColumn(0);
    this->setPickSelector(mSelector);
    this->connect(mSelector, SIGNAL(selected(QString)), this, SLOT(onSelected()));
}

void LanguageSelector::setValue(const QString &value) {
    bool found = false;
    int i = 0;

    while ((!found) && (i < mModel->rowCount())) {
        found = mModel->value(i).toString() == value;

        if (found) {
            mSelector->setCurrentIndex(i);
        }

        i++;
    }

    if (!found) {
        mSelector->setCurrentIndex(0);
    }
}

QString LanguageSelector::currentValue() {
    return mModel->value(mSelector->currentIndex()).toString();
}

void LanguageSelector::onSelected() {
    Q_EMIT valueChanged(this->currentValue());
}

void LanguageSelector::hideUnavailableLanguages() {
    QDir dir("/opt/microbe/translations");
    QStringList availableLanguages = dir.entryList(QStringList("*.qm"), QDir::Files);
    QList<int> rowsToRemove;

    for (int i = 0; i < mModel->rowCount(); i++) {
        QString lang = mModel->value(i).toString();

        if (!availableLanguages.contains(QString("microbe_%1.qm").arg(lang))) {
            rowsToRemove.prepend(i);
        }
        else {
            availableLanguages.removeOne(lang);
        }
    }

    while (!rowsToRemove.isEmpty()) {
        mModel->removeRows(rowsToRemove.takeFirst(), 1);
    }
}
