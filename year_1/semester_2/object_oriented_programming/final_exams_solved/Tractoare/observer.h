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
	void notify() const;
	void addObs(Observer*newObs);
	void delObs(Observer* toDelObs);
};