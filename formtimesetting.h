#ifndef FORMTIMESETTING_H
#define FORMTIMESETTING_H

#include <QWidget>

namespace Ui {
class FormTimeSetting;
}

class FormTimeSetting : public QWidget
{
    Q_OBJECT

public:
    explicit FormTimeSetting(QWidget *parent = 0);
    ~FormTimeSetting();

private slots:
    void on_pushButton_return_clicked();

private:
    Ui::FormTimeSetting *ui;
};

#endif // FORMTIMESETTING_H
