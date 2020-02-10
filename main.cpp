#include "widget.h"
#include <QApplication>
#include <QStyle>
#include <QStyleFactory>
#include "commthread.h"
#include "globalvariable.h"
#include "communicationtomcu.h"

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", "tgtsml");
    QApplication a(argc, argv);
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    Widget w;
    w.show();

//    ComThread dt;
//    dt.setStackSize(1024 * 1024 * 4);
//    dt.start();

    return a.exec();
}
