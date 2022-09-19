#pragma once
#include "repository.h"
#include "observer.h"

class Service : public Observable {
private:
	Repository& repo;
public:
	Service(Repository& nrepo) : repo(nrepo) { }

	void add(string ndim, string nsquares, string nplayer);
	void act(int nid, string ndim, string nsquares, string nplayer, string nstage);
	void played(int id, int row, int col);

	int size();
	Game operator[](const int& id);
	vector <Game> getAll();
};