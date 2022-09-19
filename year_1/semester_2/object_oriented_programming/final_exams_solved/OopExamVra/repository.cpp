#include "repository.h"


void Repository::writeInFile() {
	ofstream outFile;
	outFile.open(fileName);
	for (auto g : v) {
		outFile << g.toString() << "\n";
	}
	outFile.close();
}

void Repository::add(string ndim, string nsqares, string nplayer, string nstg) {
	Game newGame(lastId++, stoi(ndim), nsqares, nplayer[0], nstg);
	v.push_back(newGame);
	writeInFile();
}

void Repository::add(int nid, string ndim, string nsqares, string nplayer, string nstg) {
	Game newGame(nid, stoi(ndim), nsqares, nplayer[0], nstg);
	v.push_back(newGame);
	writeInFile();
}

void Repository::del(int nid) {
	auto posit = find_if(v.begin(), v.end(), [&](Game& g) {
		return nid == g.getId();
		});
	v.erase(posit);
}

void Repository::played(int id, int row, int col) {
	auto posit = find_if(v.begin(), v.end(), [&](Game& g) { return g.getId() == id; });
	int pos = distance(v.begin(), posit);
	v[pos].played(row, col);
}

int Repository::size() {
	return v.size();
}

vector <Game> Repository::getAll() {
	return v;
}
