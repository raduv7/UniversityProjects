#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_simularePractic.h"

class simularePractic : public QMainWindow
{
    Q_OBJECT

public:
    simularePractic(QWidget *parent = Q_NULLPTR);

private:
    Ui::simularePracticClass ui;
};
