#pragma once
#include "domain.h"
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <vector>
#include <algorithm>

class Repository {
private:
	vector <BundleElement> v;

	vector<BundleElement>::iterator findPos(const BundleElement& toSrchElem) {
		return find(v.begin(), v.end(), toSrchElem);
	}

public:
	Repository(const string fileName) {
		ifstream inFile;
		string vals[3], exVal0;
		inFile.open(fileName);
		for (exVal0 = "", getline(inFile, vals[0], ';'), getline(inFile, vals[1], ';'), getline(inFile, vals[2]); exVal0 != vals[0]; exVal0 = vals[0], getline(inFile, vals[0], ';'), getline(inFile, vals[1], ';'), getline(inFile, vals[2])) {
			BundleElement newElem(vals[0], vals[1], vals[2]);
			v.push_back(newElem);
		}
	}

	~Repository() = default;

	bool add(BundleElement newElem) {
		auto pos = findPos(newElem);
		if (pos != v.end()) {
			return false;
		}
		v.push_back(newElem);
		return true;

	}

	bool del(const BundleElement&toDelElem) {
		auto pos = findPos(toDelElem);
		if (pos == v.end()) {
			return false;
		}
		v.erase(pos);
		return true;
	}
	void clear() {
		v.clear();
	}

	vector <BundleElement> getAll() const {
		vector <BundleElement> ret(v);
		return ret;
	}

	int size() const {
		return v.size();
	}

};