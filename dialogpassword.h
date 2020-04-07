#ifndef DIALOGPASSWORD_H
#define DIALOGPASSWORD_H

#include <QDialog>

namespace Ui {
class DialogPassWord;
}

class DialogPassWord : public QDialog
{
    Q_OBJECT

public:
    explicit DialogPassWord(QWidget *parent = 0);
    ~DialogPassWord();

private:
    Ui::DialogPassWord *ui;
};

#endif // DIALOGPASSWORD_H
