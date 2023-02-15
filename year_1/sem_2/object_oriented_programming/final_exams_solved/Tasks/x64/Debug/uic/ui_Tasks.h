/********************************************************************************
** Form generated from reading UI file 'Tasks.ui'
**
** Created by: Qt User Interface Compiler version 6.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKS_H
#define UI_TASKS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TasksClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TasksClass)
    {
        if (TasksClass->objectName().isEmpty())
            TasksClass->setObjectName("TasksClass");
        TasksClass->resize(600, 400);
        menuBar = new QMenuBar(TasksClass);
        menuBar->setObjectName("menuBar");
        TasksClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(TasksClass);
        mainToolBar->setObjectName("mainToolBar");
        TasksClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(TasksClass);
        centralWidget->setObjectName("centralWidget");
        TasksClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(TasksClass);
        statusBar->setObjectName("statusBar");
        TasksClass->setStatusBar(statusBar);

        retranslateUi(TasksClass);

        QMetaObject::connectSlotsByName(TasksClass);
    } // setupUi

    void retranslateUi(QMainWindow *TasksClass)
    {
        TasksClass->setWindowTitle(QCoreApplication::translate("TasksClass", "Tasks", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TasksClass: public Ui_TasksClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TASKS_H
