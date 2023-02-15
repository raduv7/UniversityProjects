#pragma once
#include "domain.h"
#include <vector>
#include <fstream>

class Repo {
private:
	vector<Song*> songs;
	string fileName;
	int lastId;

	static void readLine(ifstream&inFile, string&exline, string line[4]);

	void writeInFile() const;

	static string songValidator(string fields[3]);
public:
	Repo(const string&newFileName) : fileName(newFileName) {
		ifstream inFile;
		inFile.open(fileName);

		string exline, line[4];
		Song* newSong;
		for (lastId = 0, line[0] = "", readLine(inFile, exline, line); exline != line[0] && !line[0].empty(); readLine(inFile, exline, line)) {
			newSong = new Song(stoi(line[0]), line + 1);
			if (newSong->getId() >= lastId) {
				lastId = newSong->getId() + 1;
			}
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

	string addSong(string fields[3]);
	void delSong(int toDelId);

	vector<Song*> getAll() const;

};