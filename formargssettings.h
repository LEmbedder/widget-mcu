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
    struct SetsPara *sets,*tempsets;
    int modelSelect;/* 工作模式选择 */
    void setSets(SetsPara *set);
    int index;
    void updateUI();
    void saveParameter();
private slots:

    void on_pushButton_delete_clicked();

    void on_pushButton_save_clicked();

    void on_pushButton_return_clicked();

    void on_pushButton_copy_clicked();

    void on_pushButton_paste_clicked();
#if 0
    void on_comboBox_revealUnit_currentIndexChanged(int index);

    void on_comboBox_testPressureBigRevealUint_currentIndexChanged(int index);
#endif
private:
    Ui::FormArgsSettings *ui;

    void initParameter();
signals:
    void emitClicked(bool);
    void emitSave(struct SetsPara *set);/* 更新参数 */
};

#endif // FORMARGSSETTINGS_H
