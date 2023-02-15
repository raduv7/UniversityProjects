#pragma once
#pragma once
#include <string>
#include <cstring>
#include <sstream>
#include <vector>

using namespace std;

class Task {
private:
	int id;
	string descr, state;
	vector <string> workers;

public:
	Task() {
		id = -1;
		descr = state = "";
	}
	Task(int nid, string ndescr, string nstate, vector <string> nworkers) {
		id = nid;
		descr = ndescr;
		state = nstate;
		for (auto nworker : nworkers) {
			workers.push_back(nworker);
		}
	}
	Task(string line[4]) {
		id = stoi(line[0]);
		descr = line[1];
		state = line[2];

		string nworker, exnworker;
		istringstream is(line[3]);
		for (exnworker = "", getline(is, nworker, ','); exnworker != nworker; exnworker = nworker, getline(is, nworker, ',')) {
			workers.push_back(nworker);
		}
	}
	Task(const Task& n) {
		id = n.id;
		descr = n.descr;
		state = n.state;
		for (auto nworker : n.workers) {
			workers.push_back(nworker);
		}
	}

	int getId() const;
	string getDescr() const;
	void setState(string nstate);
	string getState() const;
	int getWorkersNr() const;
	bool hasWorker(string srchWorker) const;

	string toString() const;
};
