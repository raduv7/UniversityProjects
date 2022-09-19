#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ExamRestante.h"

class ExamRestante : public QMainWindow
{
    Q_OBJECT

public:
    ExamRestante(QWidget *parent = nullptr);
    ~ExamRestante();

private:
    Ui::ExamRestanteClass ui;
};
