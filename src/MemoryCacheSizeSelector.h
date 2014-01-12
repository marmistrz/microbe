#ifndef MEMORYCACHESIZESELECTOR_H
#define MEMORYCACHESIZESELECTOR_H

#include "Enums.h"
#include <QMaemo5ValueButton>

class MemoryCacheSizeModel;
class QMaemo5ListPickSelector;

class MemoryCacheSizeSelector : public QMaemo5ValueButton
{
    Q_OBJECT

public:
    explicit MemoryCacheSizeSelector(const QString &text, QWidget *parent = 0);
    void setValue(signed int value);
    signed int currentValue();

private Q_SLOTS:
    void onSelected();

Q_SIGNALS:
    void valueChanged(signed int value);

private:
    MemoryCacheSizeModel *mModel;
    QMaemo5ListPickSelector *mSelector;
};

#endif // MEMORYCACHESIZESELECTOR_H
