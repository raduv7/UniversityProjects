#include "gui.h"
#include "tests.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    testAll();
    Repository repo("data.txt");
    Service srv(repo);
    Gui guy(&srv);
    guy.show();
    return a.exec();
}
