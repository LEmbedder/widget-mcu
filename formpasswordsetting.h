#ifndef FORMPASSWORDSETTING_H
#define FORMPASSWORDSETTING_H

#include <QWidget>
#include "globalvariable.h"
#include <QSettings>
#include <QFile>

namespace Ui {
class FormPasswordSetting;
}

class FormPasswordSetting : public QWidget
{
    Q_OBJECT

public:
    explicit FormPasswordSetting(QWidget *parent = 0);
    ~FormPasswordSetting();

    void init();
private slots:
    void on_pushButton_return_clicked();

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_pushButton_clicked();

private:
    Ui::FormPasswordSetting *ui;
};

#endif // FORMPASSWORDSETTING_H
