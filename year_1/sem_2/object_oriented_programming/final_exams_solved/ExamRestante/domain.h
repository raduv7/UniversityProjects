#pragma once
#include <string>
#include <cstring>

using namespace std;

class Prod {
private:
	int id;
	double price;
	string name, type;
public:
	Prod(string fields[4]) {
		id = stoi(fields[0]);
		price = stod(fields[1]);
		name = fields[2];
		type = fields[3];
	}

	int getId() const;
	/// no input
	/// no errors
	/// <returns> the id </returns>
	double getPrice() const;
	/// no input
	/// no errors
	/// <returns> the price </returns>
	string getName() const;
	/// no input
	/// no errors
	/// <returns> the name </returns>
	string getType() const;
	/// no input
	/// no errors
	/// <returns> the type </returns>
	string toString() const;
	/// no input
	/// no errors
	/// <returns> all fields combined and an \n </returns>
};