#include "service.h"

void Service::add(string line[4]) {
	repo.add(line);
	notify();
}

void Service::update(int id, string nstate) {
	repo.update(id, nstate);
	notify();
}


vector<Task> Service::getAll() const {
	vector<Task> ret = repo.getAll();
	sort(ret.begin(), ret.end(), [](const Task& task1, const Task& task2)
		{
			return task1.getState() > task2.getState();
		});
	return ret;
}
vector<Task> Service::getAll(int srchStateCode) const {
	string srchState;
	if (srchStateCode == 0) {
		srchState = "open";
	}
	else if (srchStateCode == 1) {
		srchState = "inprogress";
	}
	else {
		srchState = "closed";
	}
	vector<Task> all = getAll();
	vector<Task> ret(all.size());
	auto it = copy_if(all.begin(), all.end(), ret.begin(), [&](Task tsk) { return tsk.getState() == srchState; });
	ret.resize(distance(ret.begin(), it));
	return ret;
}
vector<Task> Service::getAll(string srchWorker) const {
	vector<Task> all = getAll();
	vector<Task> ret(all.size());
	auto it = copy_if(all.begin(), all.end(), ret.begin(), [&](Task tsk) { return tsk.hasWorker(srchWorker); });
	ret.resize(distance(ret.begin(), it));
	return ret;
}