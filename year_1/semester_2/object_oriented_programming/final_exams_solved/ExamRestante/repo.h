#pragma once
#include "domain.h"
#include <vector>
#include <fstream>

class Repo {
private:
	vector<Prod*> prods;
	string fileName;

	static void readLine(ifstream&inFile, string&exline, string line[4]);
	void writeInFile();
	string prodValidator(string fields[4]);
public:
	Repo(string newFileName) : fileName(newFileName) {
		/// citirea din fisier se face din formatul <id>;<price>;<name>;<type>
		/// no exceptions
		/// <param name="newFileName"> should be a valid file name, otherwise repo is empty </param>
		ifstream inFile;
		inFile.open(fileName);

		string exline, line[4];
		Prod* newProd;
		for (line[0] = "", readLine(inFile, exline, line); exline != line[0] && !line[0].empty(); readLine(inFile, exline, line)) {
			if (prodValidator(line).empty()) {
				newProd = new Prod(line);
				prods.push_back(newProd);
			}
			else {
				throw("Sir, currupted file!");
			}
		}
		inFile.close();
	}
	~Repo() {
		writeInFile();
	}
	string add(string fields[4]);
	/// input: fields
	/// if valid, adds new Product in repo
	/// <returns> possible errors </returns>

	vector<Prod*> getAll() const;
	/// input: no
	/// no excdeptions
	/// 
	/// <returns> all prods </returns>
};