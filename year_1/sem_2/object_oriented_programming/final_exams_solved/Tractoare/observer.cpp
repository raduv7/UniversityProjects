#include "observer.h"

void Observable::notify() const {
	for(auto obs: obss) {
		obs->update();
	}
}

void Observable::addObs(Observer* newObs) {
	obss.push_back(newObs);
}

void Observable::delObs(Observer* toDelObs) {
	for (auto it = obss.begin(); it != obss.end(); ++it) {
		if ((*it) == toDelObs) {
			obss.erase(it);
			break;
		}
	}
}


