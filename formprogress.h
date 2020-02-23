#ifndef FORMPROGRESS_H
#define FORMPROGRESS_H

#include <QWidget>
#include "globalvariable.h"
#include <QDebug>

namespace Ui {
class FormProgress;
}

class FormProgress : public QWidget
{
    Q_OBJECT

public:
    explicit FormProgress(QWidget *parent = 0);
    ~FormProgress();

    bool setProgressValue(int value);
    void resetProgressValue();
//    void updateProgressText();
    virtual void paintEvent(QPaintEvent *event);
private:
    Ui::FormProgress *ui;
};

#endif // FORMPROGRESS_H
