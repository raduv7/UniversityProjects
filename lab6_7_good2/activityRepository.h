#pragma once
#pragma once

#include "activity.h"
#include <vector>
#include <string>

using namespace std;

class ActivityRepository {
public:
    explicit ActivityRepository(const string& fileName);
    ~ActivityRepository();

    bool findActivity(const string& toFindName, Activity& foundActivity) const;
    bool add(const Activity& toAddActivity);
    bool del(const string& toDelName);
    void delAll();
    void sort(const bool& orderAsc, const int& field);

    vector <Activity> getAll() const;

private:
    string fileName;
    //MyVector ar;

    vector <Activity> ar;

    int findPos(const string& toFindName) const;
};
