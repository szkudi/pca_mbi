#include <QtGui/QApplication>
#include "mainwindow.h"
#include "controller.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Controller mainController(&w);
    mainController.init();
    return a.exec();
}
