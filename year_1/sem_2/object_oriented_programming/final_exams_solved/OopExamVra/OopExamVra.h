#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_OopExamVra.h"

class OopExamVra : public QMainWindow
{
    Q_OBJECT

public:
    OopExamVra(QWidget *parent = Q_NULLPTR);

private:
    Ui::OopExamVraClass ui;
};
