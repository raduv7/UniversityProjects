/********************************************************************************
** Form generated from reading UI file 'OopExamVra.ui'
**
** Created by: Qt User Interface Compiler version 6.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OOPEXAMVRA_H
#define UI_OOPEXAMVRA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OopExamVraClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *OopExamVraClass)
    {
        if (OopExamVraClass->objectName().isEmpty())
            OopExamVraClass->setObjectName("OopExamVraClass");
        OopExamVraClass->resize(600, 400);
        menuBar = new QMenuBar(OopExamVraClass);
        menuBar->setObjectName("menuBar");
        OopExamVraClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(OopExamVraClass);
        mainToolBar->setObjectName("mainToolBar");
        OopExamVraClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(OopExamVraClass);
        centralWidget->setObjectName("centralWidget");
        OopExamVraClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(OopExamVraClass);
        statusBar->setObjectName("statusBar");
        OopExamVraClass->setStatusBar(statusBar);

        retranslateUi(OopExamVraClass);

        QMetaObject::connectSlotsByName(OopExamVraClass);
    } // setupUi

    void retranslateUi(QMainWindow *OopExamVraClass)
    {
        OopExamVraClass->setWindowTitle(QCoreApplication::translate("OopExamVraClass", "OopExamVra", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OopExamVraClass: public Ui_OopExamVraClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OOPEXAMVRA_H
