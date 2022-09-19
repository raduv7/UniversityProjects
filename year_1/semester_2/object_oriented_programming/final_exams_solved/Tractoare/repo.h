#pragma once
#include "domain.h"
#include <vector>
#include <fstream>

class Repo {
private:
	vector<Tractor*> cars;
	string fileName;

	static void readLine(ifstream& inFile, string& exline, string line[4]);
	void writeInFile() const;
	string carValidator(string fields[4]);

public:
	Repo(const string& newFileName) : fileName(newFileName) {
		ifstream inFile;
		inFile.open(fileName);

		string exline, line[4];
		Tractor* newCar;
		for (line[0] = "", readLine(inFile, exline, line); !line[0].empty() && exline != line[0]; readLine(inFile, exline, line)) {
			if (carValidator(line).empty()) {
				newCar = new Tractor(line);
				cars.push_back(newCar);
			}
		}

		inFile.close();
	}
	~Repo() {
		writeInFile();
		for (auto car : cars) {
			delete car;
		}
	}

	string addCar(string fields[4]);
	void updCar(int updId);

	vector<Tractor*> getAll() const;
};