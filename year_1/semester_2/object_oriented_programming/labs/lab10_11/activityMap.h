#pragma once
#pragma once
#pragma once
#pragma once

#include "activity.h"

class ReportItem {
private:
	string type;
	int count;

public:
	ReportItem(string newType);

	void inc();
	bool equ(string& otherType);

	void display();

};