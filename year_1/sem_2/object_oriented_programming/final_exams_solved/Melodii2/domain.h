#pragma once
#include <string>
#include <cstring>

using namespace std;

class Song {
private:
	int id;
	string name, writer, genre;
public:
	Song(int newId, string fields[3]) {
		id = newId;
		name = fields[0];
		writer = fields[1];
		genre = fields[2];
	}

	int getId() const;
	string getName() const;
	string getWriter() const;
	string getGenre() const;
	string toString() const;
};