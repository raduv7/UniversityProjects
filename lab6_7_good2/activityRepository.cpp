//
// Created by Radu on 3/28/2022.
//

#include "activityRepository.h"
//#include <cstdio>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <algorithm>

using namespace std;

ActivityRepository::ActivityRepository(const string& fileNameStr) {
    /**
     * the constructor gets a file name, reads and saves all lines
     */
    fileName = fileNameStr;
    if (fileNameStr.empty()) {
        return;
    }

    //    // declaring character array
    //    char fileNameChrP[fileNameStr.length() + 1];
    //    // copying the contents of the string to char array
    //    strcpy(fileNameChrP, fileNameStr.c_str());
    //    FILE* file = fopen(fileNameChrP,"r");
    //    char readLine[128];

    //    cout << "check1";
    ifstream fin(fileName);
    string readLine, exReadLine;
    getline(fin, readLine);
    for (int i = 0; !readLine.empty() && readLine != exReadLine; ++i) {
        //        cout << "check2";
                /// process and read new line

        cout << readLine << "\n";

        Activity newActivity(readLine);

        string testLine;
        newActivity.activityToLine(testLine);
        cout << testLine << "\n";

        ar.push_back(newActivity);
        exReadLine = readLine;
        getline(fin, readLine);
    }
}

ActivityRepository::~ActivityRepository() {

    // declaring character array
    int i;
    char fileNameChrP[1024];

    // copying the contents of the
    // string to char array
    strcpy_s(fileNameChrP, fileName.c_str());
    ofstream fout(fileNameChrP);
    string toWriteLineStr;
    for (i = 0; i < ar.size(); ++i) {
        ar[i].activityToLine(toWriteLineStr);
        fout << toWriteLineStr;
    }
    // ar.~MyVector();
}

int ActivityRepository::findPos(const string& toFindName) const {
    /*
    int i;
    for (i = 0; i < ar.size(); ++i) {
        if (ar[i].getName() == toFindName) {
            return i;
        }
    }*/
    auto pos = find_if(ar.begin(), ar.end(), [toFindName](const Activity& act) { return act.getName() == toFindName; });
    if (pos == ar.end()) {

        return -1;
    }
    else {
        return pos - ar.begin();
    }
}

bool ActivityRepository::findActivity(const string& toFindName, Activity& foundActivity) const {
    int i;
    for (i = 0; i < ar.size(); ++i) {
        if (ar[i].getName() == toFindName) {
            foundActivity = ar[i];
            return true;
        }
    }
    return false;
}

bool ActivityRepository::add(const Activity& toAddActivity) {
    if (toAddActivity.getTime() == -1) {
        return false;
    }
    if (findPos(toAddActivity.getName()) >= 0) {
        return false;
    }
    else {
        ar.push_back(toAddActivity);
        return true;
    }
}

bool ActivityRepository::del(const string& toDelName) {
    int pos = findPos(toDelName);
    if (pos >= 0) {
        //ar.erase(MyVector::begin() + pos);
        ar.erase(ar.begin() + pos);
        return true;
    }
    else {
        return false;
    }
}

void ActivityRepository::delAll() {
    ar.clear();
}

void ActivityRepository::sort(const bool& orderAsc, const int& field) {
    // ar.sort(orderAsc, field);
    if (orderAsc) {
        if (field == 1) {
            std::sort(ar.begin(), ar.end(), [](Activity& a1, Activity& a2) {return a1.getName() < a2.getName(); });
        }
        else if (field == 2) {
            std::sort(ar.begin(), ar.end(), [](Activity& a1, Activity& a2) {return a1.getDescr() < a2.getDescr(); });
        }
        else if (field == 3) {
            std::sort(ar.begin(), ar.end(), [](Activity& a1, Activity& a2) {return a1.getType() < a2.getType(); });
        }
        else if (field == 4) {
            std::sort(ar.begin(), ar.end(), [](Activity& a1, Activity& a2) {return a1.getTime() < a2.getTime(); });
        }
    }
    else {
        if (field == 1) {
            std::sort(ar.begin(), ar.end(), [](Activity& a1, Activity& a2) {return a1.getName() > a2.getName(); });
        }
        else if (field == 2) {
            std::sort(ar.begin(), ar.end(), [](Activity& a1, Activity& a2) {return a1.getDescr() > a2.getDescr(); });
        }
        else if (field == 3) {
            std::sort(ar.begin(), ar.end(), [](Activity& a1, Activity& a2) {return a1.getType() > a2.getType(); });
        }
        else if (field == 4) {
            std::sort(ar.begin(), ar.end(), [](Activity& a1, Activity& a2) {return a1.getTime() > a2.getTime(); });
        }
    }
}

vector <Activity> ActivityRepository::getAll() const {
    int i;
    vector <Activity> sol;
    for (i = 0; i < ar.size(); ++i) {
        sol.push_back(ar[i]);
    }
    return sol;
}
