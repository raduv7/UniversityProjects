#include "simularePractic.h"
#include "Gui.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    simularePractic w;
    string fileName = "data.txt";
    Repository repo(fileName);
    Service srv(repo);
    GUI guy(srv);
    guy.show();
    return a.exec();
}
