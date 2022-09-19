#pragma once
#include "repo.h"
#include "observer.h"
#include <algorithm>

class Service : public Observable {
private:
	Repo* repo;
public:
	Service(Repo*newRepo) : repo(newRepo) { }

	string addSong(string fields[3]);
	void delSong(int toDelId);

	vector<Song*> getAll() const;
	int countWriter(string srchWriter) const;
	int countGenre(string srchGenre) const;
	vector<int> countAllGenres() const;
};