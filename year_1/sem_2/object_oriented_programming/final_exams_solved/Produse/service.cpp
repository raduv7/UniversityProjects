#include "service.h"

string Service::addProd(string fields[4]) {
	string ret = repo->addProd(fields);
	notify();
	return ret;
}

int Service::prodCounter(string type) const {
	vector<Product*> prods(repo->getAll());
	return count_if(prods.begin(), prods.end(), [&](Product* prod) { return prod->getType() == type; });
}

vector<string> Service::getAllTypes() const {
	vector<string> types;
	vector<Product*> prods(repo->getAll());
	sort(prods.begin(), prods.end(), [&](Product*prod1, Product*prod2) { return prod1->getType() < prod2->getType(); });
	if (prods.empty()) {
		return types;
	}
	int i;
	for(i=1, types.push_back(prods[0]->getType()); i < prods.size(); ++i) {
		if (prods[i]->getType() != prods[i - 1]->getType()) {
			types.push_back(prods[i]->getType());
		}
	}
	return types;
}

vector<Product*> Service::getAll(int maxPrice) const {
	vector<Product*> prods(repo->getAll());
	vector<Product*> ret(prods.size());
	auto it = copy_if(prods.begin(), prods.end(), ret.begin(), [&](Product* prod) { return prod->getPrice() <= maxPrice; });
	ret.resize(distance(ret.begin(), it));
	sort(ret.begin(), ret.end(), [&](Product* prod1, Product* prod2) { return prod1->getPrice() < prod2->getPrice(); });
	return ret;
}

Product* Service::operator [](int pos) const {
	return getAll()[pos];
}