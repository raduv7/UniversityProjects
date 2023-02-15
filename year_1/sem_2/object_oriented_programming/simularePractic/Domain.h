#pragma once

#include <string>
#include <cstring>

using namespace std;

class Device {
private:
	string type, model, color;
	int year, price;
public:
	Device(string nType, string nModel, string nColor, string nYear, string nPrice);
	Device(const Device& other);
	Device() {};
	~Device();

	bool operator=(const Device&other) const;

	string getType() const;
	string getModel() const;
	string getColor() const;
	int getYear() const;
	int getPrice() const;

	void setType(string ntype);
	void setModel(string nmodel);
	void setColor(string color);
	void setYear(int nyear);
	void setPrice(int nprice);
	void swp(Device& other);

};