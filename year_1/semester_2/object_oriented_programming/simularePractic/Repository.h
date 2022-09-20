#pragma once
#include "Domain.h"
#include <vector>

class Repository {
private:
	vector <Device> v;

public:
	Repository(const string fileName);
	~Repository();

	Device find(const string type);

	vector <Device> getAll();
	Device getOnly(string model);
};