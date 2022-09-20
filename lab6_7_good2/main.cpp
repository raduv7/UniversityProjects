#include "tests.h"
#include "menu.h"
#include <iostream>
#define _CRTDBG_MAP_ALLOC
using namespace std;

int main2() {
    cout << "marian e prost\n";
    cout << _CrtDumpMemoryLeaks() << "\n";
    cout << "marian e prost 2 \n";
    testAll();
    cout << "marian e prost\n";
    cout << _CrtDumpMemoryLeaks() << "\n";
    cout << "marian e prost 2 \n";
    printf("All tests passed, sir!\n");
    ActivityRepository repo("data.txt");
    ActivityService srv(repo);
    UserInterface ui(srv);
    //repo.~ActivityRepository();
    return 0;
}

int main() {
    main2();
    cout << "memory leaks: \n";
    cout << _CrtDumpMemoryLeaks() << "\n";
    cout << " \n";
    return 0;
}
