#pragma once
#pragma once
#include <vector>

using namespace std;

class Observer {
public:
	virtual void update() = 0;
};

class Observable {
private:
	vector<Observer*> obss;
public:
	void notify() {
		for (auto obs : obss) {
			obs->update();
		}
	}
	void addObserver(Observer* nobs) {
		obss.push_back(nobs);
	}
	void delObserver(Observer* delobs) {
		for (auto it = obss.begin(); it != obss.end(); ++it) {
			if (*it == delobs) {
				obss.erase(it);
				// delete delobs;
				break;
			}
		}
	}
};