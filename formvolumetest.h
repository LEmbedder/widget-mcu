#ifndef FORMVOLUMETEST_H
#define FORMVOLUMETEST_H

#include <QWidget>
#include "globalvariable.h"
#include <QSettings>
#include <QFile>

namespace Ui {
class FormVolumeTest;
}

class FormVolumeTest : public QWidget
{
    Q_OBJECT

public:
    explicit FormVolumeTest(QWidget *parent = 0);
    ~FormVolumeTest();

    void loadPara();
    void savePara();
    void updateForm();
private slots:
    void on_pushButton_ok_clicked();

private:
    Ui::FormVolumeTest *ui;
};

#endif // FORMVOLUMETEST_H
