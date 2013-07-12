#ifndef QTTEST_H
#define QTTEST_H

#include <qapplication.h>
#include "ui_qttest.h"

class QtTest : public QMainWindow {
    Q_OBJECT

public:
    QtTest ( QWidget *parent = 0 );
    ~QtTest();

private:
    Ui::QtTestClass ui;
};

#endif // QTTEST_H
