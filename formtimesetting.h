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

    void on_pushButton_setted_clicked();

private:
    Ui::FormTimeSetting *ui;
    QString timeString;
};

#endif // FORMTIMESETTING_H
