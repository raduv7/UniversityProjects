#include "gui.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repository repo("data.txt");
    Service srv(repo);
    Gui guy(&srv);
    guy.show();
    return a.exec();
}
