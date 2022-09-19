#include "domain.h"

void Song::setRank(int newRank) {
	if (newRank > 10) {
		rank = 10;
	}
	else if (newRank < 0) {
		rank = 0;
	}
	else {
		rank = newRank;
	}
}

void Song::setName(string newName) {
	name = newName;
}

int Song::getId() const {
	return id;
}

int Song::getRank() const {
	return rank;
}

string Song::getName() const {
	return name;
}

string Song::getWriter() const {
	return writer;
}

string Song::toString() const {
	string ret = "";
	ret += to_string(id);
	ret += ';';
	ret += to_string(rank);
	ret += ';';
	ret += name;
	ret += ';';
	ret += writer;
	ret += '\n';
	return ret;
}