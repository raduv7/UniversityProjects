#pragma once
#include <cstring>
#include <string>

using namespace std;

class Song {
private:
	int id;
	int rank;
	string name, writer;
public:
	Song(string fields[4]) {
		id = stoi(fields[0]);
		rank = stoi(fields[1]);
		name = fields[2];
		writer = fields[3];
	}

	void setRank(int newRank);
	void setName(string newName);

	int getId() const;
	int getRank() const;
	string getName() const;
	string getWriter() const;

	string toString() const;
};