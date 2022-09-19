#include "domain.h"

int Product::getId() const {
	return id;
}

double Product::getPrice() const {
	return price;
}

string Product::getName() const {
	return name;
}

string Product::getType() const {
	return type;
}

int Product::getVowelsNr() const {
	int vowelsNr = 0;
	for (auto chr : name) {
		if (strchr("aeiouAEIOU", chr) != NULL) {
			++vowelsNr;
		}
	}
	return vowelsNr;
}