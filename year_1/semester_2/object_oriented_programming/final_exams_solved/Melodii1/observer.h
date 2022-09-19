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

	void addObs(Observer*newObs) {
		obss.push_back(newObs);
	}

	void delObs(Observer* delObs) {
		for (auto it = obss.begin(); it != obss.end(); ++it) {
			if (*it == delObs) {
				obss.erase(it);
			}
		}
	}
};