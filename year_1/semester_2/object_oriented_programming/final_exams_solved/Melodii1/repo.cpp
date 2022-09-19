#include "repo.h"

void Repo::writeInFile() const {
	ofstream outFile;
	outFile.open(fileName);
	for (auto song : songs) {
		outFile << song->toString();
	}
	outFile.close();
}

void Repo::readLine(ifstream& inFile, string& exline, string line[4]) {
	exline = line[0];
	getline(inFile, line[0], ';');
	getline(inFile, line[1], ';');
	getline(inFile, line[2], ';');
	getline(inFile, line[3]);
}

void Repo::delSong(int delId) {
	for (auto it = songs.begin(); it != songs.end(); ++it) {
		if ((*it)->getId() == delId) {
			songs.erase(it);
			break;
		}
	}
	writeInFile();
}

void Repo::updateSong(int updId, int newRank, string newName) {
	for (auto it = songs.begin(); it != songs.end(); ++it) {
		if ((*it)->getId() == updId) {
			(*it)->setName(newName);
			(*it)->setRank(newRank);
			break;
		}
	}
	writeInFile();
}

vector<Song*> Repo::getAll() const {
	vector<Song*> ret(songs);
	return ret;
}