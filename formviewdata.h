#ifndef FORMVIEWDATA_H
#define FORMVIEWDATA_H

#include <QWidget>

namespace Ui {
class FormViewData;
}

class FormViewData : public QWidget
{
    Q_OBJECT

public:
    explicit FormViewData(QWidget *parent = 0);
    ~FormViewData();

private:
    Ui::FormViewData *ui;
};

#endif // FORMVIEWDATA_H
