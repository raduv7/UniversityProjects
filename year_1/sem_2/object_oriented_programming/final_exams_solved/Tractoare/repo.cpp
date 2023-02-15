#include "repo.h"

void Repo::readLine(ifstream& inFile, string& exline, string line[4]) {
	exline = line[0];
	getline(inFile, line[0], ';');
	getline(inFile, line[1], ';');
	getline(inFile, line[2], ';');
	getline(inFile, line[3]);
}

void Repo::writeInFile() const {
	ofstream outFile;
	outFile.open(fileName);
	for (auto car : cars) {
		outFile << car->toString();
	}
	outFile.close();
}

string Repo::carValidator(string fields[4]) {
	string ret = "";
	try {
		int testInt = stoi(fields[0]);
		if (testInt < 0) {
			ret += "Sir, id must be a positive integer!\n";
		}
		else {
			for (auto car : cars) {
				if (car->getId() == testInt) {
					ret += "Sir, there is already a tractor with this id!\n";
					break;
				}
			}
		}
	}
	catch (...) {
		ret += "Sir, id must be an integer!\n";
	}
	try {
		int testInt = stoi(fields[1]);
		if (testInt < 2) {
			ret += "Sir, the number of wheels must be a positive integer greater than 1!\n";
		}
		if (testInt > 16) {
			ret += "Sir, the number of wheels must be an integer smaller than 17!\n";
		}
		if (testInt % 2) {
			ret += "Sir, the number of wheels must pe an even number!\n";
		}
	}
	catch (...) {
		ret += "Sir, the number of wheels must be an integer!\n";
	}

	if (fields[2].empty()) {
		ret += "Sir, the name must not be empty!\n";
	}
	for (auto chr : fields[2]) {
		if (chr == ';') {
			ret += "Sir, the name must not have any \';\' in it!\n";
		}
	}

	if (fields[3].empty()) {
		ret += "Sir, the type must not be empty!\n";
	}
	for (auto chr : fields[3]) {
		if (chr == ';') {
			ret += "Sir, the type must not have any \';\' in it!\n";
		}
	}
	return ret;
}

string Repo::addCar(string fields[4]) {
	string ret = carValidator(fields);
	if (ret.empty()) {
		Tractor* newCar = new Tractor(fields);
		cars.push_back(newCar);
	}
	writeInFile();
	return ret;
}

void Repo::updCar(int updId) {
	for (auto car : cars) {
		if (car->getId() == updId) {
			-- (*car);
		}
	}
	writeInFile();
}

vector<Tractor*> Repo::getAll() const {
	vector<Tractor*> ret(cars);
	return ret;
}