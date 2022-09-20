/********************************************************************************
** Form generated from reading UI file 'simularePractic.ui'
**
** Created by: Qt User Interface Compiler version 6.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMULAREPRACTIC_H
#define UI_SIMULAREPRACTIC_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_simularePracticClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *simularePracticClass)
    {
        if (simularePracticClass->objectName().isEmpty())
            simularePracticClass->setObjectName("simularePracticClass");
        simularePracticClass->resize(600, 400);
        menuBar = new QMenuBar(simularePracticClass);
        menuBar->setObjectName("menuBar");
        simularePracticClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(simularePracticClass);
        mainToolBar->setObjectName("mainToolBar");
        simularePracticClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(simularePracticClass);
        centralWidget->setObjectName("centralWidget");
        simularePracticClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(simularePracticClass);
        statusBar->setObjectName("statusBar");
        simularePracticClass->setStatusBar(statusBar);

        retranslateUi(simularePracticClass);

        QMetaObject::connectSlotsByName(simularePracticClass);
    } // setupUi

    void retranslateUi(QMainWindow *simularePracticClass)
    {
        simularePracticClass->setWindowTitle(QCoreApplication::translate("simularePracticClass", "simularePractic", nullptr));
    } // retranslateUi

};

namespace Ui {
    class simularePracticClass: public Ui_simularePracticClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMULAREPRACTIC_H
