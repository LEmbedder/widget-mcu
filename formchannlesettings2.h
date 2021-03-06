#ifndef FORMCHANNLESETTINGS2_H
#define FORMCHANNLESETTINGS2_H

#include <QWidget>
#include <QPushButton>
#include <QSettings>
#include <QFile>
#include "formargssettings.h"
#include "globalvariable.h"


namespace Ui {
class FormChannleSettings2;
}

class FormChannleSettings2 : public QWidget
{
    Q_OBJECT

public:
    explicit FormChannleSettings2(QWidget *parent = 0);
    ~FormChannleSettings2();
    QPushButton *bt1;
    QPushButton *bt2;
    QPushButton *bt3;
    QPushButton *bt4;
    QPushButton *bt5;
    QPushButton *bt6;
    QPushButton *bt7;
    QPushButton *bt8;
    QPushButton *bt9;
    QPushButton *bt10;
    QPushButton *bt11;
    QPushButton *bt12;
    QPushButton *bt13;
    QPushButton *bt14;
    QPushButton *bt15;
    QPushButton *bt16;
    void initSets(int );
    void loadParam(QString number);
    void updateChannelDesc();
public slots:
    void soltUpdataSets(struct SetsPara *set);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_06_clicked();

    void on_pushButton_03_clicked();

    void on_pushButton_02_clicked();

    void on_pushButton_04_clicked();

    void on_pushButton_05_clicked();

    void on_pushButton_07_clicked();

    void on_pushButton_08_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_09_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void savePara();
private:
    Ui::FormChannleSettings2 *ui;
    FormArgsSettings *fas;
    QString page;/* 当前页面 */
    int page_int;


};

#endif // FORMCHANNLESETTINGS2_H
