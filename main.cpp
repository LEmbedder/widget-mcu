#include "widget.h"
#include <QApplication>
#include <QStyle>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", "tgtsml");
    QApplication a(argc, argv);
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    Widget w;
    w.show();

    return a.exec();
}
