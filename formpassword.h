#ifndef FORMPASSWORD_H
#define FORMPASSWORD_H

#include <QWidget>
#include <QSettings>
#include <QFile>
#include "globalvariable.h"
#include <QDebug>

namespace Ui {
class FormPassword;
}

class FormPassword : public QWidget
{
    Q_OBJECT

public:
    explicit FormPassword(QWidget *parent = 0);
    ~FormPassword();
    void passWordReset();
    bool isTrue;
    int type;/* 0:main 1:system 2:time 3:password 4:fix 5:reset 6:extend */
    void clearText();
private slots:
    void on_pushButton_clicked();

private:
    Ui::FormPassword *ui;
    void loadPassword();
signals:
    void emitIsTrue();
    void emitIsTrue_2();
    void emitIsTrue_3();
    void emitIsTrue_4();
    void emitIsTrue_5();
    void emitIsTrue_6();
};

#endif // FORMPASSWORD_H
