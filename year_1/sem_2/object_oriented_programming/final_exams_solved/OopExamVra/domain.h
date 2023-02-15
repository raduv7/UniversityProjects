#pragma once
#include <string>
#include <cstring>

using namespace std;


class Game {
private:
	int id = -1, dim = 0;
	string squares = "";
	char player = 'a';
	string stg = "";
public:
	Game() {}
	Game(int nid, int ndim, string nsquares, char nplayer, string nstg) : id(nid), dim(ndim), squares(nsquares), player(nplayer), stg(nstg) {}
	Game(const Game&n) : id(n.id), dim(n.dim), squares(n.squares), player(n.player), stg(n.stg) {}

	Game& operator = (const Game& other);
	bool operator==(const Game& other) const;

	int getId() const;
	int getDim() const;
	string getSquares() const;
	char getPlayer() const;
	string getStg() const;

	void played(int row, int col) {
		if (player == 'X') {
			squares[row * dim + col] =  'X';
			player = 'O';
		}
		else {
			squares[row * dim + col] = 'O';
			player = 'X';
		}
	}

	string toString() const;
};
