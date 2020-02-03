#ifndef FORMARGSSETTINGS_H
#define FORMARGSSETTINGS_H

#include <QWidget>
#include <QDialog>
#include <QString>
#include "config.h"

namespace Ui {
class FormArgsSettings;
}


class FormArgsSettings : public QDialog
{
    Q_OBJECT

public:
    explicit FormArgsSettings(QDialog *parent = 0);
    ~FormArgsSettings();
    struct SetsPara *sets;
    int modelSelect;/* 工作模式选择 */
    void setSets(SetsPara *set);
    int index;
    void updateUI();
    void saveParameter();
private slots:

    void on_pushButton_delete_clicked();

    void on_pushButton_save_clicked();

    void on_pushButton_return_clicked();

private:
    Ui::FormArgsSettings *ui;

    void initParameter();
signals:
    void emitClicked(bool);
    void emitSave(struct SetsPara *set);/* 更新参数 */
};

#endif // FORMARGSSETTINGS_H
