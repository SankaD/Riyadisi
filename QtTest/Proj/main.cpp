#include "proj.h"
#include "mainwindow.h"
#include <QtGui/QApplication>

int main ( int argc, char *argv[] )
{
    QApplication a ( argc, argv );

    MainWindow m;
    m.show();
    return a.exec();

}
