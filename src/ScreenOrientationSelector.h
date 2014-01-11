#ifndef SCREENORIENTATIONSELECTOR_H
#define SCREENORIENTATIONSELECTOR_H

#include "Enums.h"
#include <QMaemo5ValueButton>

class ScreenOrientationModel;
class QMaemo5ListPickSelector;

class ScreenOrientationSelector : public QMaemo5ValueButton
{
    Q_OBJECT

public:
    explicit ScreenOrientationSelector(const QString &text, QWidget *parent = 0);
    void setValue(ScreenOrientation::Orientation value);
    ScreenOrientation::Orientation currentValue();

private slots:
    void onSelected();

signals:
    void valueChanged(ScreenOrientation::Orientation value);

private:
    ScreenOrientationModel *mModel;
    QMaemo5ListPickSelector *mSelector;
};

#endif // SCREENORIENTATIONSELECTOR_H
