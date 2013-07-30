/********************************************************************************
** Form generated from reading UI file 'proj.ui'
**
** Created: Tue Jul 16 20:51:07 2013
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROJ_H
#define UI_PROJ_H

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

class Ui_ProjClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ProjClass)
    {
        if (ProjClass->objectName().isEmpty())
            ProjClass->setObjectName(QString::fromUtf8("ProjClass"));
        ProjClass->resize(600, 400);
        menuBar = new QMenuBar(ProjClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        ProjClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ProjClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        ProjClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(ProjClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        ProjClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ProjClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        ProjClass->setStatusBar(statusBar);

        retranslateUi(ProjClass);

        QMetaObject::connectSlotsByName(ProjClass);
    } // setupUi

    void retranslateUi(QMainWindow *ProjClass)
    {
        ProjClass->setWindowTitle(QApplication::translate("ProjClass", "Proj", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ProjClass: public Ui_ProjClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROJ_H
