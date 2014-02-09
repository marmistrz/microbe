#ifndef SEARCHENGINESELECTOR_H
#define SEARCHENGINESELECTOR_H

#include "Enums.h"
#include <QMaemo5ValueButton>

class SearchEngineModel;
class QMaemo5ListPickSelector;

class SearchEngineSelector : public QMaemo5ValueButton
{
    Q_OBJECT

public:
    explicit SearchEngineSelector(const QString &text, QWidget *parent = 0);
    void setValue(signed int value);
    signed int currentValue();

private Q_SLOTS:
    void onSelected();

Q_SIGNALS:
    void valueChanged(signed int value);

private:
    SearchEngineModel *mModel;
    QMaemo5ListPickSelector *mSelector;
};

#endif // SEARCHENGINESELECTOR_H
