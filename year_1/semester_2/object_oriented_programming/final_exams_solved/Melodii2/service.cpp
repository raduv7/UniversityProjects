#include "service.h"

string Service::addSong(string fields[3]) {
	string ret = repo->addSong(fields);
	notify();
	return ret;
}

void Service::delSong(int toDelId) {
	repo->delSong(toDelId);
	notify();
}

vector<Song*> Service::getAll() const {
	vector<Song*> ret(repo->getAll());
	sort(ret.begin(), ret.end(), [&](Song* song1, Song* song2) { return song1->getWriter() < song2->getWriter(); });
	return ret;
}

int Service::countWriter(string srchWriter) const {
	vector<Song*> all(getAll());
	int cnt = 0;
	for (auto song : all) {
		if (song->getWriter() == srchWriter) {
			++ cnt;
		}
	}
	return cnt;
}

int Service::countGenre(string srchGenre) const {
	vector<Song*> all(getAll());
	int cnt = 0;
	for (auto song : all) {
		if (song->getGenre() == srchGenre) {
			++ cnt;
		}
	}
	return cnt;
}

vector<int> Service::countAllGenres() const { 
	vector<int> ret;
	ret.push_back(countGenre("rock"));
	ret.push_back(countGenre("folk"));
	ret.push_back(countGenre("pop"));
	ret.push_back(countGenre("disco"));
	return ret;
}