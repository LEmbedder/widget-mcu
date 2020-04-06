#ifndef DIALOGMESSAGE_H
#define DIALOGMESSAGE_H

#include <QDialog>

namespace Ui {
class DialogMessage;
}

class DialogMessage : public QDialog
{
    Q_OBJECT

public:
    explicit DialogMessage(QWidget *parent = 0);
    ~DialogMessage();

    void showMessage(int timer = 2000, QString message = "", QColor color = Qt::red);
private slots:
    void closeMessage();
private:
    Ui::DialogMessage *ui;
    bool isOpen;
};

#endif // DIALOGMESSAGE_H
