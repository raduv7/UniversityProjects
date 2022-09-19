#pragma once
#include "repo.h"
#include "observer.h"
#include <algorithm>

class Service : public Observable {
private:
	Repo* repo;
public:
	Service(Repo* newRepo) : repo(newRepo) { }

	string addCar(string fields[4]);
	void updCar(int updId);

	Tractor* getCarById(int srchId) const;
	int getSameType(string srchType) const;
	vector<string> getTypes() const;
	vector<Tractor*> getAll() const;
};