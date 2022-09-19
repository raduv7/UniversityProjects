#pragma once
#include <vector>

using namespace std;

class Observer {
public:
	virtual void update() = 0;
};

class Observable {
private:
	vector<Observer*> obs;

public:
	void notify() {
		for (auto ob : obs) {
			ob->update();
		}
	}

	void addOb(Observer*nob) {
		obs.push_back(nob);
	}

	void delOb(Observer* nob) {
		for (auto it = obs.begin(); it != obs.end(); ++it) {
			if (*it == nob) {
				obs.erase(it);
			}
		}
	}
};