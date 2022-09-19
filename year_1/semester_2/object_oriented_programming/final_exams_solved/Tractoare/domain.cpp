#include "domain.h"

void Tractor::operator--() {
	if (wheels > 2) {
		wheels -= 2;
	}
}

int Tractor::getId() const {
	return id;
}

int Tractor::getWheels() const {
	return wheels;
}

string Tractor::getName() const {
	return name;
}

string Tractor::getType() const {
	return type;
}

string Tractor::toString() const {
	string ret = "";
	ret += to_string(id);
	ret += ";";
	ret += to_string(wheels);
	ret += ";";
	ret += name;
	ret += ";";
	ret += type;
	ret += "\n";
	return ret;
}