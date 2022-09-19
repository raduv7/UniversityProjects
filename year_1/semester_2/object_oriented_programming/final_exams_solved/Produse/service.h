#pragma once
#include "repo.h"
#include "observe.h"

class Service : public Observable {
private:
	Repository* repo;
public:
	Service(Repository*nrepo) : repo(nrepo) { }

	string addProd(string fields[4]);

	int prodCounter(string type) const;
	vector<string> getAllTypes() const;
	vector<Product*> getAll(int maxPrice = 100) const;
	Product* operator [](int pos) const;
};