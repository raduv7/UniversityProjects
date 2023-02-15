#include "lab13_14.h"
#include "gui.h"
#include "tests.h"

int main(int argc, char *argv[])
{
    testAll();
    QApplication a(argc, argv);
    // lab13_14 w;
    Repository repo("data.txt");
    Service srv(repo);
    GUI guy(&srv);
    guy.show();
    return a.exec();
}
