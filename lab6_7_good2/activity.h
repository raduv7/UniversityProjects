#pragma once
#pragma once

#include <string>

using namespace std;

class Activity {
public:

    Activity();
    explicit Activity(const string& line);
    Activity(const Activity& toCopyActivity);
    void activityToLine(string& newLine) const;

    bool operator==(const Activity& other) const;
    Activity& operator=(const Activity& other);

    string getName() const;
    string getDescr() const;
    string getType() const;
    int getTime() const;

private:
    string name, descr, type;
    int time;
};
