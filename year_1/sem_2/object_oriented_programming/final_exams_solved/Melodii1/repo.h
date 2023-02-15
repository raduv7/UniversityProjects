#pragma once
#include "domain.h"
#include <vector>
#include <fstream>

class Repo {
private:
	string fileName;
	vector<Song*> songs;

	void writeInFile() const;
	void readLine(ifstream&inFile, string&exline, string line[4]);
public:
	Repo(const string&newFileName) : fileName(newFileName) {
		ifstream inFile;
		inFile.open(fileName);

		string exline, line[4];
		Song* newSong;
		for (line[0] = "", readLine(inFile, exline, line); exline != line[0] && !line[0].empty(); readLine(inFile, exline, line)) {
			newSong = new Song(line);
			songs.push_back(newSong);
		}

		inFile.close();
	}
	~Repo() {
		writeInFile();
		for (auto song : songs) {
			delete song;
		}
	}

	void delSong(int delId);
	void updateSong(int updId, int newRank, string newName);

	vector<Song*> getAll() const;
};