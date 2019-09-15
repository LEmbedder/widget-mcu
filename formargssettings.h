#ifndef FORMARGSSETTINGS_H
#define FORMARGSSETTINGS_H

#include <QWidget>
#include <QDialog>
namespace Ui {
class FormArgsSettings;
}

class FormArgsSettings : public QDialog
{
    Q_OBJECT

public:
    explicit FormArgsSettings(QDialog *parent = 0);
    ~FormArgsSettings();

private slots:
    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::FormArgsSettings *ui;
signals:
    void emitClicked(bool);
};

#endif // FORMARGSSETTINGS_H
