#include "service.h"

string Service::add(string fields[4]) {
	string ret = repo->add(fields);
	notify();
	return ret;
}

int Service::countType(string type) const {
	vector<Prod*> all(repo->getAll());
	return count_if(all.begin(), all.end(), [&](Prod* prod1) { return prod1->getType() == type; });
}

vector<Prod*> Service::getAll() const {
	vector<Prod*> ret(repo->getAll());
	sort(ret.begin(), ret.end(), [&](Prod* prod1, Prod* prod2) { 
		string cmp1, cmp2;
		for (auto chr : prod1->getName()) {
			cmp1 += tolower(tolower(chr));
		}
		for (auto chr : prod2->getName()) {
			cmp2 += tolower(tolower(chr));
		}
		return cmp1 < cmp2; });
	return ret;
}
vector<string> Service::getTypes() const {
	vector<string> ret;
	vector<Prod*> all(repo->getAll());
	sort(all.begin(), all.end(), [&](Prod* prod1, Prod* prod2) { return prod1->getType() < prod2->getType(); });
	if (all.empty()) {
		return ret;
	}
	int i;

	for (ret.push_back(all[0]->getType()), i = 1; i < all.size(); ++i) {
	
		if (all[i]->getType() != all[i-1]->getType()) {
			ret.push_back(all[i]->getType());
		}
	}
	return ret;
}