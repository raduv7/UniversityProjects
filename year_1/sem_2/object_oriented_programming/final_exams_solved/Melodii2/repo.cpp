#include "repo.h"

void Repo::readLine(ifstream&inFile, string&exline, string line[4]) {
	exline = line[0];
	getline(inFile, line[0], ';');
	getline(inFile, line[1], ';');
	getline(inFile, line[2], ';');
	getline(inFile, line[3]);
}

void Repo::writeInFile() const {
	ofstream outFile;
	outFile.open(fileName);
	for (auto song : songs) {
		outFile << song->toString();
	}
	outFile.close();
}

string Repo::songValidator(string fields[3]) {
	string reterr = "";

	if (fields[0].empty()) {
		reterr += "Sir, you must enter a name!\n";
	}
	for (auto chr : fields[0]) {
		if (chr == ';') {
			reterr += "Sir, the title cannot contain \';\'\n";
		}
	}

	if (fields[1].empty()) {
		reterr += "Sir, you must enter a writer!\n";
	}
	for (auto chr : fields[1]) {
		if (chr == ';') {
			reterr += "Sir, the author cannot contain \';\'\n";
		}
	}

	if (fields[2].empty()) {
		reterr += "Sir, you must enter a genre!\n";
	}
	for (auto chr : fields[2]) {
		if (chr == ';') {
			reterr += "Sir, the genre cannot contain \';\'\n";
		}
	}
	if (fields[2] != "pop" && fields[2] != "rock" && fields[2] != "folk" && fields[2] != "disco") {
		reterr += "Sir, the genre must be a good one!\n";
	}
	return reterr;
}

string Repo::addSong(string fields[3]) {
	string reterr = "";
	if (lastId >= (1 << 30)) {
		reterr += "Sir, too many songs!\n";
	}
	reterr += songValidator(fields);
	if (reterr.empty()) {
		Song* newSong = new Song(lastId ++, fields);
		songs.push_back(newSong);
		writeInFile();
	}
	return reterr;
}

void Repo::delSong(int toDelId) {
	for (auto it = songs.begin(); it != songs.end(); ++ it) {
		if ((*it)->getId() == toDelId) {
			songs.erase(it);
			break;
		}
	}
	writeInFile();
}

vector<Song*> Repo::getAll() const {
	vector<Song*> ret(songs);
	return ret;
}