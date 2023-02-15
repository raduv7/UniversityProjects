#include "domain.h"

Game& Game::operator=(const Game&other) {
	id = other.getId();
	dim = other.getDim();
	squares = other.getSquares();
	player = other.getPlayer();
	stg = other.getStg();
	return *this;
}

bool Game::operator==(const Game& other) const {
	return id == other.getId();
}

int Game::getId() const {
	return id;
}

int Game::getDim() const {
	return dim;
}

string Game::getSquares() const {
	return squares;
}

char Game::getPlayer() const {
	return player;
}

string Game::getStg() const {
	return stg;
}

string Game::toString() const {
	string ret = "";
	ret += (char) ('0' + getDim());
	ret += ";";
	ret += getSquares();
	ret += ";";
	ret += getPlayer();
	ret += ";";
	ret += getStg();
	return ret;
}