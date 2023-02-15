#include "Produse.h"
#include "gui.h"
#include "tests.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    testAll();

    QApplication a(argc, argv);
    Repository repo("data.txt");
    Service srv(&repo);
    Gui guy(&srv);
    guy.show();
    return a.exec();
}
