#pragma once
#include "repo.h"
#include "observer.h"
#include <algorithm>

class Service : public Observable {
private:
	Repo* repo;
public:
	Service(Repo*newRepo) : repo(newRepo) {	}

	string delSong(int delId);
	string updSong(int updId, int newRank, string newName);

	int countSongsAtRank(int srchRank) const;
	int countSongsAtWriter(string srchWriter) const;
	vector<Song*> getAll() const;
	vector<int> getAllRanks() const;
};
