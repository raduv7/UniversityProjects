#pragma once
#include "Repository.h"

class Service {
private:
	Repository repo;
public:
	Service(Repository&newRepo);
	~Service();

	Device find(const string type);

	vector <Device> getAll();
	vector <Device> getSortedModel();
	vector <Device> getSortedPrice();
	Device getOnly(string model);
};