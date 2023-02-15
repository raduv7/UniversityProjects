#pragma once
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include "domain.h"


class Repository {
private:
	int lastId;
	string fileName;
	vector <Game> v;

public:
	Repository(const string& nFileName) : fileName(nFileName) {
		ifstream inFile;
		inFile.open(fileName);

		string exvals[4], vals[4];
		lastId = 0;
		for (exvals[0] = "", exvals[1] = "", exvals[2] = "", exvals[3] = "",
			getline(inFile, vals[0], ';'),
			getline(inFile, vals[1], ';'),
			getline(inFile, vals[2], ';'),
			getline(inFile, vals[3]);
				(exvals[0] != vals[0] || exvals[1] != vals[1] || exvals[2] != vals[2] || exvals[3] != vals[3]) && !vals[0].empty();
			exvals[0] = vals[0],
			exvals[1] = vals[1],
			exvals[2] = vals[2],
			exvals[3] = vals[3],
			getline(inFile, vals[0], ';'),
			getline(inFile, vals[1], ';'),
			getline(inFile, vals[2], ';'),
			getline(inFile, vals[3])) {
			Game newGame(lastId++, stoi(vals[0]), vals[1], (char) vals[2][0], vals[3]);
			v.push_back(newGame);
		}

		inFile.close();
	}
	~Repository() {
		writeInFile();
	}

	void writeInFile();

	void add(string ndim, string nsqares, string nplayer, string nstg);
	void add(int nid, string ndim, string nsqares, string nplayer, string nstg);
	void del(int nid);
	void played(int id, int row, int col);

	int size();
	vector <Game> getAll();
};