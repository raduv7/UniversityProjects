#pragma once
#include <vector>
using namespace std;


class Observer {
public:
	virtual void update() = 0;
};

class Observable {
private:
	vector <Observer*> obss;
public:
	void notify();
	void addObs(Observer* nobs);
	void delObs(Observer* nobs);
};