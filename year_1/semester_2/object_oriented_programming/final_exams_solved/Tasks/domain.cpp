#include "domain.h"

int Task::getId() const {
	return id;
}

string Task::getDescr() const {
	return descr;
}

void Task::setState(string nstate) {
	state = nstate;
}

string Task::getState() const {
	return state;
}

int Task::getWorkersNr() const {
	return workers.size();
}

bool Task::hasWorker(string srchWorker) const {
	for (auto worker : workers) {
		if (worker == srchWorker) {
			return true;
		}
	}
	return false;
}

string Task::toString() const {
	int i;
	string ret = "";
	ret += to_string(id);
	ret += ";";
	ret += descr;
	ret += ";";
	ret += state;
	ret += ";";
	for (i = 1, ret += workers[0]; i < workers.size(); ++i) {
		ret += ",";
		ret += workers[i];
	}
	ret += "\n";
	return ret;
}
