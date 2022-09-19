#pragma once
#include <string>
#include <cstring>

using namespace std;

class Tractor {
private:
	int id, wheels;
	string name, type;
public:
	Tractor(string fields[4]) {
		id = stoi(fields[0]);
		wheels = stoi(fields[1]);
		name = fields[2];
		type = fields[3];
	}

	void operator --();

	int getId() const;
	int getWheels() const;
	string getName() const;
	string getType() const;
	string toString() const;
};