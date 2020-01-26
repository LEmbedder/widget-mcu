#ifndef FORMSYSTEMSETTING_H
#define FORMSYSTEMSETTING_H

#include <QWidget>
#include "config.h"
#include <QStringList>
#include <string.h>

namespace Ui {
class FormSystemSetting;
}

/* 界面参数配置 */
struct Args_config {
    int model;
    int worker_space;
    int A_model;
    int B_model;
    int product_model;
};
class FormSystemSetting : public QWidget
{
    Q_OBJECT

public:
    explicit FormSystemSetting(QWidget *parent = 0);
    ~FormSystemSetting();
    struct Args_config args_config;
    struct Args_config args_config_temp;
    void update_system_setting();
    QString return_model();
    QString return_worker_space();
private slots:
    void on_pushButton_return_clicked();

    void on_comboBoxModelSelect_currentIndexChanged(int index);

    void on_pushButton_save_clicked();

    void on_comboBox_worker_currentIndexChanged(int index);

    void on_comboBox_a_worker_currentIndexChanged(int index);

    void on_comboBox_b_worker_currentIndexChanged(int index);

    void on_comboBox_product_model_currentIndexChanged(int index);

private:
    Ui::FormSystemSetting *ui;
    signals:
    void emit_update_config(struct Args_config*);
};

#endif // FORMSYSTEMSETTING_H
