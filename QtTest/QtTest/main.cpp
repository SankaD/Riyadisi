#include <qttest.h>
#include <qapplication.h>

int main ( int argc, char *argv[] )
{
    QApplication a ( argc, argv );
    QtTest w;
    w.show();
    return a.exec();
}
