#ifndef STACKEDWINDOW_H
#define STACKEDWINDOW_H

#include <QComboBox>

class AddressBar : public QComboBox
{
    Q_OBJECT

public:
    explicit AddressBar(QWidget *parent = 0);
    ~AddressBar() {}

public Q_SLOTS:
    void onLoadProgressChanged();
    void onURLChanged();

Q_SIGNALS:
    void URLRequest(const QString url);

protected Q_SLOTS:
    void onReturnPressed();

protected:

private:
};

#endif // STACKEDWINDOW_H
