//
// Created by Radu on 3/28/2022.
//

#include "activityService.h"
#include <algorithm>
#include <string>

ActivityService::ActivityService(ActivityRepository& repo) : repo(repo) {}

ActivityService::~ActivityService() {
    // repo.destructor();

    UndoActions* act = NULL;

    while (!Actions.empty()) {
        act = Actions.back();
        Actions.pop_back();
        delete act;
    }
}

int randomInt() {
    return rand() % 100;
}

string randomWord() {
    string sol = "";
    int len = (rand() % 12) + 4, i;
    for (i = 0; i < len; ++i) {
        sol += ('a' + (rand() % 26));
    }
    return sol;
}

string generateActivityLine(string name) {
    string sol = "";
    string types[4] = { "sport","familie","societate","munca" };
    if (name.empty()) {
        sol += randomWord();
    }
    else {
        sol += name;
    }
    sol += ";";
    sol += randomWord();
    sol += ";";
    sol += types[randomInt() % 4];
    sol += ";";
    sol += to_string(randomInt());
    //sol += "\n";
    return sol;
}

bool ActivityService::add(const string& line) {
    Activity toAddActivity(line);

    Actions.push_back(new UndoAdd(repo, toAddActivity));
    return repo.add(toAddActivity);
}


bool ActivityService::generateByName(const string& line) {
    if (-1 != line.find(";")) {
        return false;
    }
    if (line.empty()) {
        return false;
    }
    Activity toAddActivity(generateActivityLine(line));
    return repo.add(toAddActivity);
    // return true;
}

bool ActivityService::generateAll(const string& line) {
    int len = stoi(line), i;
    if (len < 0 || len > 1024) {
        return false;
    }
    for (i = 0; i < len; ++i) {
        Activity toAddActivity(generateActivityLine(""));
        repo.add(toAddActivity);
    }
    return true;
}

bool ActivityService::del(const string& line) {
    Activity deletedAct;
    bool ret = repo.findActivity(line, deletedAct);
    repo.del(line);
    if (ret) {
        Actions.push_back(new UndoRemove(repo, deletedAct));
    }
    return ret;
}

void ActivityService::delAll() {
    repo.delAll();
}

bool ActivityService::update(const string& line) {
    Activity updatedAct;
    Activity toUpdateActivity(line);
    bool ret = repo.findActivity(toUpdateActivity.getName(), updatedAct);
    repo.del(line);
    if (ret) {
        Actions.push_back(new UndoChange(repo, updatedAct, toUpdateActivity));
    }
    if (repo.del(toUpdateActivity.getName())) {
        return repo.add(toUpdateActivity);
    }
    else {
        return false;
    }
}

bool ActivityService::findActivity(const string& line, string& toPrint) {
    Activity toPrintActivity;
    if (repo.findActivity(line, toPrintActivity)) {
        toPrintActivity.activityToLine(toPrint);
        return true;
    }
    else {
        toPrint = "";
        return false;
    }
}


void ActivityService::undo() {
    if (Actions.empty()) {
        return;
    }
    else {
        UndoActions* act = Actions.back();
        act->doUndo();
        Actions.pop_back();
        delete act;

    }
}



void ActivityService::sort(const string& order, const string& field) {
    bool toSortOrderAsc;
    int toSortField;
    if (order == "asc") {
        toSortOrderAsc = true;
    }
    else if (order == "desc") {
        toSortOrderAsc = false;
    }
    else {
        return;
    }

    if (field == "name") {
        toSortField = 1;
    }
    else if (field == "description") {
        toSortField = 2;
    }
    else if (field == "type") {
        toSortField = 3;
    }
    else if (field == "duration") {
        toSortField = 4;
    }
    else {
        return;
    }
    repo.sort(toSortOrderAsc, toSortField);
}



unordered_map <string, ReportItem> ActivityService::reportTypes() {
    vector <Activity> acts = getAll("", "");
    unordered_map <string, ReportItem> sol;
    bool alreadyInMap;
    for (auto& act : acts) {
        alreadyInMap = false;
        string type = act.getType();
        for (auto& mapItem : sol) {
            if (mapItem.second.equ(type)) {
                mapItem.second.inc();
                alreadyInMap = true;
                break;
            }
        }
        if (!alreadyInMap) {
            ReportItem newType(type);
            //sol.insert(std::make_pair<string, ReportItem> (type, newType));
            sol.insert({ {type, newType} });
        }
    }
    return sol;
}


vector <Activity> ActivityService::getAll(const string& flirtDescr, const string& flirtType) const {
    //int i;
    vector <Activity> toFilter;
    toFilter = repo.getAll();
    vector<Activity> sol(toFilter.size());
    /*
    for (i = 0; i < sol.size(); ++i) {
        if (!((flirtDescr.empty() || sol[i].getDescr() == flirtDescr) && (flirtType.empty() || sol[i].getType() == flirtType))) {
            sol.erase(sol.begin() + i);
            --i;
        }
    }
    */
    auto solLen = copy_if(toFilter.begin(), toFilter.end(), sol.begin(), [flirtDescr, flirtType](Activity& act) { return ((flirtDescr.empty() || act.getDescr() == flirtDescr) && (flirtType.empty() || act.getType() == flirtType)); });
    sol.resize(std::distance(sol.begin(), solLen));
    //copy_if(toFilter.begin(), toFilter.end(), sol.begin(), [flirtDescr,flirtType](Activity act) { return true; });
    return sol;
}
