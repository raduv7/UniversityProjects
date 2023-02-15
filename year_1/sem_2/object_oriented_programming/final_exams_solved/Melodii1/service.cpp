#include "service.h"

string Service::delSong(int delId) {
	string reterr = "";
	if (delId == -1) {
		reterr += "Sir, you must select a song!\n";
	}
	if (reterr.empty()) {
		repo->delSong(delId);
		notify();
	}
	return reterr;
}

string Service::updSong(int updId, int newRank, string newName) {
	string reterr = "";
	if (updId == -1) {
		reterr += "Sir, you didn't select a song to update!\n";
	}
	if (reterr.empty()) {
		repo->updateSong(updId, newRank, newName);
		notify();
	}
	return reterr;
}


int Service::countSongsAtRank(int srchRank) const {
	int ret = 0;
	vector<Song*> all = getAll();
	for (auto song: all) {
		if (song->getRank() == srchRank) {
			++ ret;
		}
	}
	return ret;
}

int Service::countSongsAtWriter(string srchWriter) const {
	int ret = 0;
	vector<Song*> all = getAll();
	for (auto song : all) {
		if (song->getWriter() == srchWriter) {
			++ret;
		}
	}
	return ret;
}

vector<Song*> Service::getAll() const {
	vector<Song*> ret(repo->getAll());
	sort(ret.begin(), ret.end(), [&](Song* song1, Song* song2) { return song1->getRank() < song2->getRank(); });
	return ret;
}

vector<int> Service::getAllRanks() const {
	vector<int> ret(11);
	vector<Song*> all(repo->getAll());
	for (auto song : all) {
		if (song->getRank() <= 10 || song->getRank() >= 0) {
			++ret[song->getRank()];
		}
	}
	return ret;
}