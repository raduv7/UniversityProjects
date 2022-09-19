#include "repo.h"

void Repo::readLine(ifstream& inFile, string& exline, string line[4]) {
	exline = line[0];
	getline(inFile, line[0], ';');
	getline(inFile, line[1], ';');
	getline(inFile, line[2], ';');
	getline(inFile, line[3]);
}

void Repo::writeInFile() {
	ofstream outFile;
	outFile.open(fileName);
	for (auto prod : prods) {
		outFile << prod->toString();
	}
	outFile.close();
}
string Repo::prodValidator(string fields[4]) {
	string ret = "";
	try {
		int testint = stoi(fields[0]);
		if (testint < 0) {
			ret += "Sir, the id must be a positive number!\n";
		}
		else {
			for (auto prod : prods) {
				if (prod->getId() == testint) {
					ret += "Sir, the id is already used!\n";
					break;
				}
			}
		}
	}
	catch (...) {
		ret += "Sir, the id must be a number!\n";
	}
	try {
		double testd = stod(fields[1]);
		if (testd < 1) {
			ret += "Sir, the price must be a number greter than 1!\n";
		}
		else if (testd > 100) {
			ret += "Sir, the price must be a number lower than 100!\n";
		}
	}
	catch (...) {
		ret += "Sir, the price must be a floating point number!\n";
	}

	if (fields[2].empty()) {
		ret += "Sir, the name must not be empty!\n";
	}
	for (auto chr : fields[2]) {
		if (chr == ';') {
			ret += "Sir, the name must not contain \';\'!\n";
		}
	}
	for (auto chr : fields[3]) {
		if (chr == ';') {
			ret += "Sir, the type must not contain \';\'!\n";
		}
	}
	return ret;
}

string Repo::add(string fields[4]) {
	string ret = prodValidator(fields);
	if (ret.empty()) {
		Prod* newProd = new Prod(fields);
		prods.push_back(newProd);
		writeInFile();
	}
	return ret;
}

vector<Prod*> Repo::getAll() const {
	vector<Prod*> ret(prods);
	return ret;
}