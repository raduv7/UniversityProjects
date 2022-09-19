#pragma once
#pragma once
#include "domain.h"
#include <vector>
#include <fstream>

class Repository {
private:
	vector<Task> tasks;
	string fileName;
public:
	Repository(string nfileName) {
		fileName = nfileName;

		ifstream inFile;
		inFile.open(fileName);

		string exid, line[4];
		line[0] = "";
		do {
			exid = line[0];
			getline(inFile, line[0], ';');
			getline(inFile, line[1], ';');
			getline(inFile, line[2], ';');
			getline(inFile, line[3]);
			if (taskValidator(line)) {
				Task ntask(line);
				tasks.push_back(ntask);
			}
		} while (exid != line[0] && line[0] != "");

		inFile.close();
	}
	~Repository() {
		writeInFile();
	}

	void writeInFile() const;

	void add(string line[4]);
	void update(int id, string nstate);
	bool taskValidator(string line[4]) const;

	vector<Task> getAll() const;
};