#include "service.h"

string Service::addCar(string fields[4]) {
	string ret = repo->addCar(fields);
	if (ret.empty()) {
		notify();
	}
	return ret;
}

void Service::updCar(int updId) {
	repo->updCar(updId);
	notify();
}

Tractor* Service::getCarById(int srchId) const {
	vector<Tractor*> all(getAll());
	for (auto car : all) {
		if (car->getId() == srchId) {
			return car;
		}
	}
}

int Service::getSameType(string srchType) const {
	int cnt = 0;
	vector<Tractor*> all(getAll());
	for (auto car : all) {
		if (car->getType() == srchType) {
			++cnt;
		}
	}
	return cnt;
}

vector<string> Service::getTypes() const {
	vector<string> ret;
	vector<Tractor*> all(getAll());
	sort(all.begin(), all.end(), [&](Tractor* car1, Tractor* car2) { return car1->getType() < car2->getType(); });
	if(all.empty()) {
		return ret;
	}
	int i;
	for (ret.push_back(all[0]->getType()), i = 1; i < all.size(); ++i) {
		if (all[i]->getType() != all[i - 1]->getType()) {
			ret.push_back(all[i]->getType());
		}
	}
	return ret;
}

vector<Tractor*> Service::getAll() const {
	vector<Tractor*> ret(repo->getAll());
	sort(ret.begin(), ret.end(), [&](Tractor* car1, Tractor* car2) { return car1->getName() < car2->getName(); });
	return ret;
}