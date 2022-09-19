#include "repo.h"

void Repository::readLine(ifstream& inFile, string line[4], string& exline) {
	exline = line[0];
	getline(inFile, line[0], ';');
	getline(inFile, line[1], ';');
	getline(inFile, line[2], ';');
	getline(inFile, line[3]);
}


string Repository::addProd(string fields[4]) {
	string ret = prodValidator(fields);
	if (ret.empty()) {
		Product* newProd = new Product(fields);
		prods.push_back(newProd);
	}
	return ret;
}

string Repository::prodValidator(string fields[4]) const {
	string ret = "";
	bool ok;
	try {
		int testInt = stoi(fields[0]);
		ok = true;
	}
	catch(...) {
		ok = false;
	}
	if (!ok) {
		ret += "Id is not an integer, sir!\n";
	}
	else {
		if (stoi(fields[0]) < 0) {
			ret += "Id cannot be a negative integer, sir!\n";
		}
		if (findProd(stoi(fields[0])) != nullptr) {
			ret += "Id is already used, sir!\n";
		}
	}

	try {
		double testDouble = stod(fields[1]);
		ok = true;
	}
	catch (...) {
		ok = false;
	}
	if (!ok) {
		ret += "Price is not a floating point number, sir!";
	}
	else {
		if (stod(fields[1]) < 0) {
			ret += "Price cannot be a negative floating point number, sir!\n";
		}
		else {
			if (stod(fields[1]) < 1) {
				ret += "Price cannot be lower than 1, sir!\n";
			}
			if (stod(fields[1]) > 100) {
				ret += "Price cannot be greater than 100, sir!\n";
			}
		}
	}

	if (fields[2].empty()) {
		ret += "Type cannon be empty, sir!";
	}
	for (auto chr : fields[2]) {
		if (chr == ';') {
			ret += "You cannot use the character in type\';\', sir!\n";
		}
	}

	if (fields[3].empty()) {
		ret += "Name cannon be empty, sir!";
	}
	for (auto chr : fields[3]) {
		if (chr == ';') {
			ret += "You cannot use the character in name\';\', sir!\n";
		}
	}

	return ret;
}

Product* Repository::findProd(int srchId) const {
	for (auto prod : prods) {
		if(prod->getId() == srchId) {
			return prod;
		}
	}
	return nullptr;
}

vector<Product*> Repository::getAll() {
	vector<Product*> ret(prods);
	return ret;
}