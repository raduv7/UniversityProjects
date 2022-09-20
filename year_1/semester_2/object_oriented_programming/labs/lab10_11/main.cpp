#include "lab10_11.h"
#include "menu.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);   

    ActivityRepository repoFile{ "data.txt" };

    ActivityService srv{ repoFile };
    GUI guy{ srv };

    lab10_11 w;

    guy.show();
    /*
    //gui.setWindowState(Qt::WindowMaximized);

    QWidget* wnd3 = new QWidget;
    QVBoxLayout* vL = new QVBoxLayout;
    wnd3->setLayout(vL);
    //create a detail widget
    QWidget* details = new QWidget;
    QFormLayout* fL = new QFormLayout;
    details->setLayout(fL);
    QLabel* lblName = new QLabel("Name");
    QLineEdit* txtName = new QLineEdit;
    fL->addRow(lblName, txtName);
    QLabel* lblAge = new QLabel("Age");
    QLineEdit* txtAge = new QLineEdit;
    fL->addRow(lblAge, txtAge);
    //add detail to window
    vL->addWidget(details);
    QPushButton* store = new QPushButton("&Store");
    vL->addWidget(store);
    //show window
    wnd3->show();
    */
    return app.exec();
}