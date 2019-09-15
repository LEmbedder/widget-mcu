#ifndef FORMPASSWORDSETTING_H
#define FORMPASSWORDSETTING_H

#include <QWidget>

namespace Ui {
class FormPasswordSetting;
}

class FormPasswordSetting : public QWidget
{
    Q_OBJECT

public:
    explicit FormPasswordSetting(QWidget *parent = 0);
    ~FormPasswordSetting();

private slots:
    void on_pushButton_return_clicked();

private:
    Ui::FormPasswordSetting *ui;
};

#endif // FORMPASSWORDSETTING_H
