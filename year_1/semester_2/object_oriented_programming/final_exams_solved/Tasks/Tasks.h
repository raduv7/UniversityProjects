#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Tasks.h"

class Tasks : public QMainWindow
{
    Q_OBJECT

public:
    Tasks(QWidget *parent = nullptr);
    ~Tasks();

private:
    Ui::TasksClass ui;
};
