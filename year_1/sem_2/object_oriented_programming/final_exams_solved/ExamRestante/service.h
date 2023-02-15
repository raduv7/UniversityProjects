#pragma once
#include "observer.h"
#include "repo.h"
#include <algorithm>

class Service : public Observable {
private:
	Repo* repo;
public:
	Service(Repo*newRepo) : repo(newRepo) { }

	string add(string fields[4]);

	int countType(string type) const;
	vector<Prod*> getAll() const;
	vector<string> getTypes() const;
};