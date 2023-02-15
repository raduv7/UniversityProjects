#include "Repository.h"
#include <fstream>

Repository::Repository(const string fileName) {
	ifstream inFile;
	inFile.open(fileName);

	string exvals, vals[5];

	for (exvals = "", vals[0] = "",
		getline(inFile, vals[0], ';'),
		getline(inFile, vals[1], ';'),
		getline(inFile, vals[2], ';'),
		getline(inFile, vals[3], ';'),
		getline(inFile, vals[4]);
			vals[0] != exvals;
		exvals = vals[0],
		getline(inFile, vals[0], ';'),
		getline(inFile, vals[1], ';'),
		getline(inFile, vals[2], ';'),
		getline(inFile, vals[3], ';'),
		getline(inFile, vals[4]))
	{
		Device newElem(vals[0], vals[1], vals[2], vals[3], vals[4]);
		v.push_back(newElem);
	}
}

Repository::~Repository() { }

Device Repository::find(const string type) {
	for (auto a : v) {
		if (a.getType() == type) {
			return a;
		}
	}
	Device ret("", "", "", "-1", "-1");
	return ret;
}

vector <Device> Repository::getAll() {
	vector <Device> ret(v);
	return ret;
}

Device Repository::getOnly(string model) {
	for (auto a : v) {
		if (a.getModel() == model) {
			return a;
		}
	}
}