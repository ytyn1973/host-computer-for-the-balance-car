#include "widget.h"
#include "sdv.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    MainWindow b;
    b.show();
    return a.exec();
}
