#include "observer.h"

void Observable::notify() const {
	for (auto obs : obss) {
		obs->update(7);
	}
}

void Observable::addObs(Observer* newObs) {
	obss.push_back(newObs);
}

void Observable::delObs(Observer* delObs) {
	for (auto it = obss.begin(); it != obss.end(); ++it) {
		if (*it == delObs) {
			obss.erase(it);
			break;
		}
	}
}