#include "mainwindow.h"
#include <qcustomplot.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    MainWindow w;
    w.show();
    return application.exec();
}
