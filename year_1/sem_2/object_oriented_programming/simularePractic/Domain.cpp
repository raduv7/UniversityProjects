
#include "Domain.h"

Device::Device(string nType, string nModel, string nColor, string nYear, string nPrice) : type(nType), model(nModel), color(nColor) {
	year = stoi(nYear);
	price = stoi(nPrice);
}

Device::Device(const Device& other) {
	type = other.getType();
	model = other.getModel();
	color = other.getColor();
	year = other.getYear();
	price = other.getPrice();
}

Device::~Device() {}

bool Device::operator=(const Device& other) const {
	return type == other.getType() && 
	model == other.getModel() && 
	color == other.getColor() && 
	year == other.getYear() && 
	price == other.getPrice();
}

string Device::getType() const {
	return type;
}
string Device::getModel() const {
	return model;
}
string Device::getColor() const {
	return color;
}
int Device::getYear() const {
	return year;
}
int Device::getPrice() const {
	return price;
}

void Device::setType(string ntype) {
	type = ntype;
}
void Device::setModel(string nmodel) {
	model = nmodel;
}
void Device::setColor(string ncolor) {
	color = ncolor;
}
void Device::setYear(int nyear) {
	year = nyear;
}
void Device::setPrice(int nprice) {
	price = nprice;
}

void Device::swp(Device& other) {
	string aux;
	aux = type;
	type = other.getType();
	other.setType(aux);
	aux = model;
	model = other.getModel();
	other.setModel(aux);
	aux = color;
	color = other.getColor();
	other.setColor(aux);
	int auxx = year;
	year = other.getYear();
	other.setYear(auxx);
	auxx = price;
	price = other.getPrice();
	other.setPrice(auxx);
}