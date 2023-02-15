#include "domain.h"

int Prod::getId() const {
	return id;
}

double Prod::getPrice() const {
	return price;
}

string Prod::getName() const {
	return name;
}

string Prod::getType() const {
	return type;
}

string Prod::toString() const {
	string ret = "";
	ret += to_string(id);
	ret += ';';
	ret += to_string(price);
	ret += ';';
	ret += name;
	ret += ';';
	ret += type;
	ret += '\n';
	return ret;
}