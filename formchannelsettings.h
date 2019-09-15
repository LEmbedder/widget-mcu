#ifndef FORMCHANNELSETTINGS_H
#define FORMCHANNELSETTINGS_H

#include <QWidget>
#include "formchannlesettings2.h"

namespace Ui {
class FormChannelSettings;
}

class FormChannelSettings : public QWidget
{
    Q_OBJECT

public:
    explicit FormChannelSettings(QWidget *parent = 0);
    ~FormChannelSettings();

private slots:

    void on_bt_up_clicked();

    void on_bt_next_clicked();

private:
    Ui::FormChannelSettings *ui;
    FormChannleSettings2 *fcs2_1;
    FormChannleSettings2 *fcs2_2;
    FormChannleSettings2 *fcs2_3;
    FormChannleSettings2 *fcs2_4;
    int index;
    void switchForm();

};

#endif // FORMCHANNELSETTINGS_H
