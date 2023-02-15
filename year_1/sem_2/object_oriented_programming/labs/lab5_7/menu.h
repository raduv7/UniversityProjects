#pragma once
#pragma once


#include "activityService.h"

using namespace std;

class UserInterface {
public:
    explicit UserInterface(ActivityService& srv);
private:
    ActivityService srv;
    string flirtDescr, flirtType;

    void addSubmenu();
    void updateSubmenu();
    void delSubmenu();
    void findSubmenu();
    void filterSubmenu();
    void sortSubmenu();
    void delAllSubmenu();
    void generateByNameSubmenu();
    void generateAllSubmenu();
    void reportTypesSubmenu();
    void undoSubmenu();
    void showAll();
};
