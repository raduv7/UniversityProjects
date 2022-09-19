#include "repository.h"

void Repository::writeInFile() const {
	ofstream outFile;
	outFile.open(fileName);
	for (auto task : tasks) {
		outFile << task.toString();
	}
	outFile.close();
}

void Repository::update(int id, string nstate) {
	int i;
	for (i = 0; i < tasks.size(); ++i) {
		if (tasks[i].getId() == id) {
			tasks[i].setState(nstate);
			break;
		}
	}
}

void Repository::add(string line[4]) {
	if (taskValidator(line)) {
		Task ntask(line);
		tasks.push_back(ntask);
	}
}
bool Repository::taskValidator(string line[4]) const {
	int nid;
	try {
		nid = stoi(line[0]);
	}
	catch (...) {
		return false;
	}
	for (auto task : tasks) {
		if (nid == task.getId()) {
			return false;
		}
	}
	if (line[1].empty()) {
		return false;
	}
	if (line[2] != "open" && line[2] != "inprogress" && line[2] != "closed") {
		return false;
	}

	int comas, i;
	if (line[3][0] == ',') {
		return false;
	}
	for (comas = 0, i = 1; i < line[3].length(); ++i) {
		if (line[3][i] == ',') {
			++comas;
			if (i == line[3].length() - 1) {
				return false;
			}
			if (line[3][i + 1] == ',') {
				return false;
			}
		}
	}
	if (comas < 1 && comas > 4) {
		return false;
	}
	return true;
}

vector<Task> Repository::getAll() const {
	vector<Task> ret(tasks);
	return ret;
}