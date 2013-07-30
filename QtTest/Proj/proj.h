#ifndef PROJ_H
#define PROJ_H

#include <QtGui/QMainWindow>
#include "ui_proj.h"

class Proj : public QMainWindow
{
	Q_OBJECT

public:
	Proj(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Proj();

private:
	Ui::ProjClass ui;
};

#endif // PROJ_H
