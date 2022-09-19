#pragma once
#include <string>
#include <cstring>

using namespace std;

class Product {
private:
	int id;
	double price;
	string type, name;
public:
	Product(int nid, double nprice, string ntype, string nname) : id(nid), price(nprice), type(ntype), name(nname) { }
	Product(string fields[4]) { 
		id = stoi(fields[0]);
		price = stod(fields[1]);
		type = fields[2];
		name = fields[3];
	}

	int getId() const;
	double getPrice() const;
	string getName() const ;
	string getType() const;
	int getVowelsNr() const;
};