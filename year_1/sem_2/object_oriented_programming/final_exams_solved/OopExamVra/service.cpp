#include "service.h"

void Service::add(string ndim, string nsquares, string nplayer) {
	string nstg = "Neinceput";
	repo.add(ndim, nsquares, nplayer, nstg);
	notify();
}

void Service::act(int nid, string ndim, string nsquares, string nplayer, string nstage) {
	repo.del(nid);
	repo.add(nid, ndim, nsquares, nplayer, nstage);
	notify();
}


void Service::played(int id, int row, int col) {
	repo.played(id, row, col);
	notify();
}

int Service::size() {
	return repo.size();
}

Game Service::operator[](const int& id) {
	vector <Game> v = getAll();
	auto posit = find_if(v.begin(), v.end(), [&](Game& g) { return g.getId() == id; });
	int pos = distance(v.begin(), posit);
	return v[pos];
}

vector <Game> Service::getAll() {
	vector <Game> ret;
	ret = repo.getAll();
	sort(ret.begin(), ret.end(), [](Game& g1, Game& g2) {return g1.getStg().compare(g2.getStg()) < 0; });
	return ret;
}
