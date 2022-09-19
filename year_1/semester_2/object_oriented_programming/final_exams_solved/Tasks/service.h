#pragma once
#pragma once
#include "repository.h"
#include "observer.h"
#include <algorithm>

class Service : public Observable {
private:
	Repository& repo;
public:
	Service(Repository& nrepo) : repo(nrepo) {}

	void add(string line[4]);
	void update(int id, string nstate);
	vector<Task> getAll() const;
	vector<Task> getAll(int srchStateCode) const;
	vector<Task> getAll(string srchWorker) const;
};