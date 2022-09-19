#include "observer.h"

void Observable::notify() {
	for (auto obs : obss) {
		obs->update();
	}
}

void Observable::addObs(Observer* nobs) {
	obss.push_back(nobs);
}

void Observable::delObs(Observer* nobs) {
	for (auto it = obss.begin(); it != obss.end(); it++) {
		if (*it == nobs) {
			obss.erase(it);
			break;
		}
	}
}