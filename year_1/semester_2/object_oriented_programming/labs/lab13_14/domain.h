#pragma once
#include <string>
#include <cstring>

using namespace std;

class BundleElement {
private:
	string name, type, descr;
public:
	BundleElement() {
		name = "";
		type = "";
		descr = "";
	}
	BundleElement(string newName, string newType, string newDescr) : name(newName), type(newType), descr(newDescr) {}
	BundleElement(const BundleElement&other) {
		name = other.getName();
		type = other.getType();
		descr = other.getDescr();
	}

	~BundleElement() = default;

	BundleElement& operator= (const BundleElement& other) {
		name = other.getName();
		type = other.getType();
		descr = other.getDescr();
		return *this;
	}

	bool operator== (const BundleElement& other) {
		return name == other.name;
		//  && type == other.type && descr == other.descr
	}

	void setName(string newName) { name = newName; }
	string getName() const { return name; }
	void setType(string newType) { type = newType; }
	string getType() const { return type; }
	void setDescr(string newDescr) { descr = newDescr; }
	string getDescr() const { return descr; }
};