#include "proj.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Proj w;
	w.show();
	return a.exec();
}
