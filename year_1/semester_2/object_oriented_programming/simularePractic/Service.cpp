#include "Service.h"
#include <algorithm>

Service::Service(Repository& newRepo) : repo(newRepo) { }

Service::~Service() { }

Device Service::find(const string type) {
	return repo.find(type);
}

vector <Device> Service::getAll() {
	return repo.getAll();
}

bool cmpModel(Device x, Device y) {
	return x.getModel() < y.getModel();
}

vector <Device> Service::getSortedModel() {
	vector <Device> got = repo.getAll();
	int i, j;
	for (i = 0; i < got.size(); ++i) {
		for (j = i + 1; j < got.size(); ++j) {
			if (!cmpModel(got[i], got[j])) {
				got[i].swp(got[j]);
			}
		}
	}
	sort(got.begin(), got.end(), cmpModel);
	return got;
}

bool cmpPrice(Device x, Device y) {
	return x.getPrice() < y.getPrice();
}

vector <Device> Service::getSortedPrice() {
	vector <Device> got = repo.getAll();
	int i, j;
	for (i = 0; i < got.size(); ++i) {
		for (j = i + 1; j < got.size(); ++j) {
			if (!cmpPrice(got[i], got[j])) {
				got[i].swp(got[j]);
			}
		}
	}
	sort(got.begin(), got.end(), cmpPrice);
	return got;

}

Device Service::getOnly(string model) {
	return repo.getOnly(model);
}