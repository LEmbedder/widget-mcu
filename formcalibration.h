#ifndef FORMCALIBRATION_H
#define FORMCALIBRATION_H

#include <QWidget>

namespace Ui {
class FormCalibration;
}

class FormCalibration : public QWidget
{
    Q_OBJECT

public:
    explicit FormCalibration(QWidget *parent = 0);
    ~FormCalibration();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::FormCalibration *ui;
};

#endif // FORMCALIBRATION_H
