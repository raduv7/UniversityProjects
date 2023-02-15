#pragma once
#pragma once
#pragma once


#include <unordered_map>
#include "activityMap.h"
#include "activityRepository.h"
#include "activityUndo.h"

class ActivityService {
public:
    explicit ActivityService(ActivityRepository& repo);
    ~ActivityService();

    bool add(const string& line);
    bool generateByName(const string& line);
    bool generateAll(const string& line);
    bool del(const string& line);
    void delAll();
    bool update(const string& line);
    bool findActivity(const string& line, string& toPrint);
    void sort(const string& order, const string& field);
    void undo();
    unordered_map <string, ReportItem> reportTypes();

    vector <Activity> getAll(const string& flirtDescr, const string& flirtType) const;
private:
    vector < UndoActions* > Actions;
    ActivityRepository& repo;
};
