#pragma once
#include "domain.h"
#include <vector>
#include <algorithm>
#include <fstream>

class Repository {
private:
	vector<Product*> prods;

	static void readLine(ifstream&inFile, string line[4], string&exline);
public:
	Repository(const string&fileName) {
		ifstream inFile;
		inFile.open(fileName);

		string exline, line[4] = {"","","",""};
		for (readLine(inFile, line, exline); exline!=line[0] && !line[0].empty(); readLine(inFile, line, exline)) {
			if(prodValidator(line).empty()) {
				Product* newProd = new Product(line);
				prods.push_back(newProd);
			}
			else {
				throw("Sir, data file is corrupted!");
			}
		}
	}
	~Repository() {
		for (auto prod : prods) {
			delete prod;
		}
	}

	string addProd(string fields[4]);
	Product* findProd(int srchId) const;
	string prodValidator(string fields[4]) const;

	vector<Product*> getAll();
};