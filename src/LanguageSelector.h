#ifndef LANGUAGESELECTOR_H
#define LANGUAGESELECTOR_H

#include <QMaemo5ValueButton>

class LanguageModel;
class QMaemo5ListPickSelector;

class LanguageSelector : public QMaemo5ValueButton
{
    Q_OBJECT

public:
    explicit LanguageSelector(const QString &text, bool hideUnavailable = false, QWidget *parent = 0);
    void setValue(const QString &value);
    QString currentValue();

private:
    void hideUnavailableLanguages();

private Q_SLOTS:
    void onSelected();

Q_SIGNALS:
    void valueChanged(const QString &value);

private:
    LanguageModel *mModel;
    QMaemo5ListPickSelector *mSelector;
};

#endif // LANGUAGESELECTOR_H
