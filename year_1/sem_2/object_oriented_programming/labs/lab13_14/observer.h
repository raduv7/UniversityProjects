#pragma once
#include <vector>
using namespace std;

class Observer {

public:
	virtual void update() = 0;
};

class Observable {
public:
	vector<Observer*> observerList;
	void notify()
	{
		for (auto observer : observerList)
			observer->update();
	}

	void addObserver(Observer* observer)
	{
		this->observerList.push_back(observer);
	}

	void removeObserver(Observer* observer)
	{
		for (auto it = this->observerList.begin(); it != this->observerList.end(); ++it)
		{
			if (*it == observer)
			{
				this->observerList.erase(it);
				break;
			}
		}
	}
};