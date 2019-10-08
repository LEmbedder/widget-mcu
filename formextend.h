#ifndef FORMEXTEND_H
#define FORMEXTEND_H

#include <QWidget>

namespace Ui {
class FormExtend;
}

class FormExtend : public QWidget
{
    Q_OBJECT

public:
    explicit FormExtend(QWidget *parent = 0);
    ~FormExtend();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::FormExtend *ui;
};

#endif // FORMEXTEND_H
