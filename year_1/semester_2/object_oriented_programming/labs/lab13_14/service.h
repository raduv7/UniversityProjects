#pragma once
#include <cctype>
#include "repository.h"
#include "observer.h"

class Service : Observable {
private:
	Repository repo;

	void alarmObs() {
		for (auto obs : observerList) {
			obs->update();
		}
	}

	static string generateField() {
		int newLen;
		string ret;
		for (ret = "", newLen = rand() % 10 + 3; newLen; --newLen) {
			ret += (char)('a' + rand() % 26);
		}
		ret[0] = toupper(ret[0]);
		return ret;
	}

	static BundleElement generateElem() {
		string newName = generateField();
		string newType = generateField();
		string newDescr = generateField();
		BundleElement ret(newName, newType, newDescr);
		return ret;
	}

public:
	Service(Repository&newRepo) : repo(newRepo) {}
	~Service() = default;

	bool add(string newName, string newType, string newDescr) {
		BundleElement newElem(newName, newType, newDescr);
		if (repo.add(newElem)) {
			alarmObs();
			return true;
		}
		else {
			return false;
		}
	}
	bool del(string toDelName, string toDelType, string toDelDescr) {
		BundleElement toDelElem(toDelName, toDelType, toDelDescr);
		if (repo.del(toDelElem)) {
			alarmObs();
			return true;
		}
		else {
			return false;
		}
	}

	void clear() { 
		repo.clear();
		alarmObs();
	}
	void generate() { 
		int newSize = rand() % 100 + 1;
		int i;
		srand(time(NULL));
		for (i = 0; i < newSize; ++i) {
			BundleElement newElem;
			newElem = generateElem();
			repo.add(newElem);
		}
		alarmObs();
	}

	vector <BundleElement> getAll() const { return repo.getAll(); }
	BundleElement operator[](int pos) const {
		vector <BundleElement> elems = getAll();
		return elems[pos];
	}
	int size() const { return repo.size(); }

	void addObserver(Observer* newObs) {
		observerList.push_back(newObs);
	}
};