//
// Created by Radu on 3/28/2022.
//

#include "activity.h"
#include <iostream>

bool activityLineValidator(const string& line) {
    int i, spaces;
    for (i = 0, spaces = 0; i < line.length(); ++i) {
        if (line[i] == ';') {
            ++spaces;
            if (spaces == 3) {
                ++i;
                break;
            }
        }
    }
    for (; i < line.length(); ++i) {
        if (line[i] > '9' || line[i] < '0') {
            return false;
        }
    }
    return spaces == 3;
}

string getWord(const string& line, int& pos) {
    int i;
    string sol;
    for (i = pos; i < line.length() && line[i] != ';' && line[i] != '\n'; ++i) {
        sol += line[i];
    }
    pos = i + 1;
    return sol;
}

Activity::Activity() {
    name = "";
    descr = "";
    type = "";
    time = -1;
}

Activity::Activity(const string& line) {
    if (activityLineValidator(line)) {
        int pos = 0;
        name = getWord(line, pos);
        descr = getWord(line, pos);
        type = getWord(line, pos);
        time = stoi(getWord(line, pos));
    }
    else {
        name = "";
        descr = "";
        type = "";
        time = -1;
    }
}


Activity::Activity(const Activity& toCopyActivity) {
    name = toCopyActivity.getName();
    descr = toCopyActivity.getDescr();
    type = toCopyActivity.getType();
    time = toCopyActivity.getTime();
    //    cout << "se apeleaza copy activity";
}


void Activity::activityToLine(string& newLine) const {
    newLine = "";
    newLine += name;
    newLine += ';';
    newLine += descr;
    newLine += ';';
    newLine += type;
    newLine += ';';
    newLine += to_string(time);
    newLine += '\n';
}

bool Activity::operator==(const Activity& other) const {
    return name == other.getName();
}

Activity& Activity::operator=(const Activity& other) {
    name = other.getName();
    descr = other.getDescr();
    type = other.getType();
    time = other.getTime();
    return *this;
}

string Activity::getName() const {
    return name;
}

string Activity::getDescr() const {
    return descr;
}

string Activity::getType() const {
    return type;
}

int Activity::getTime() const {
    return time;
}
