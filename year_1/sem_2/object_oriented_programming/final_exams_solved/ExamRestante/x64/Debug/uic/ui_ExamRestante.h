/********************************************************************************
** Form generated from reading UI file 'ExamRestante.ui'
**
** Created by: Qt User Interface Compiler version 6.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXAMRESTANTE_H
#define UI_EXAMRESTANTE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ExamRestanteClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ExamRestanteClass)
    {
        if (ExamRestanteClass->objectName().isEmpty())
            ExamRestanteClass->setObjectName("ExamRestanteClass");
        ExamRestanteClass->resize(600, 400);
        menuBar = new QMenuBar(ExamRestanteClass);
        menuBar->setObjectName("menuBar");
        ExamRestanteClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ExamRestanteClass);
        mainToolBar->setObjectName("mainToolBar");
        ExamRestanteClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(ExamRestanteClass);
        centralWidget->setObjectName("centralWidget");
        ExamRestanteClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ExamRestanteClass);
        statusBar->setObjectName("statusBar");
        ExamRestanteClass->setStatusBar(statusBar);

        retranslateUi(ExamRestanteClass);

        QMetaObject::connectSlotsByName(ExamRestanteClass);
    } // setupUi

    void retranslateUi(QMainWindow *ExamRestanteClass)
    {
        ExamRestanteClass->setWindowTitle(QCoreApplication::translate("ExamRestanteClass", "ExamRestante", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ExamRestanteClass: public Ui_ExamRestanteClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXAMRESTANTE_H
