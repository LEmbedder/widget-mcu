#ifndef FORMMAIN_H
#define FORMMAIN_H

#include <QWidget>
#include <QPushButton>
#include "formchannelsettings.h"
#include "formargusetting.h"

namespace Ui {
class FormMain;
}

class FormMain : public QWidget
{
    Q_OBJECT

public:
    explicit FormMain(QWidget *parent = 0);
    ~FormMain();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::FormMain *ui;
    void witchButtonChecked(QPushButton *button);
    FormChannelSettings *formChannleSettings;
    FormArguSetting *formArguSetting;
};

#endif // FORMMAIN_H
