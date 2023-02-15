#include "domain.h"

int Song::getId() const {
	return id;
}

string Song::getName() const {
	return name;
}

string Song::getWriter() const {
	return writer;
}

string Song::getGenre() const {
	return genre;
}

string Song::toString() const {
	string ret = "";
	ret += to_string(id);
	ret += ";";
	ret += name;
	ret += ";";
	ret += writer;
	ret += ";";
	ret += genre;
	ret += '\n';
	return ret;
}
