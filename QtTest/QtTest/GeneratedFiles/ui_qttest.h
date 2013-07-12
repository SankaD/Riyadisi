/********************************************************************************
** Form generated from reading UI file 'qttest.ui'
**
** Created: Wed Jul 10 17:33:08 2013
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTTEST_H
#define UI_QTTEST_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtTestClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtTestClass)
    {
        if (QtTestClass->objectName().isEmpty())
            QtTestClass->setObjectName(QString::fromUtf8("QtTestClass"));
        QtTestClass->resize(600, 400);
        menuBar = new QMenuBar(QtTestClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        QtTestClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtTestClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QtTestClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(QtTestClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QtTestClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QtTestClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QtTestClass->setStatusBar(statusBar);

        retranslateUi(QtTestClass);

        QMetaObject::connectSlotsByName(QtTestClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtTestClass)
    {
        QtTestClass->setWindowTitle(QApplication::translate("QtTestClass", "QtTest", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QtTestClass: public Ui_QtTestClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTTEST_H
