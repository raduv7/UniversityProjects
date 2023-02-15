#pragma once

#include <iostream>
#include "activityMap.h"

ReportItem::ReportItem(string newType) {
	type = newType;
	count = 1;
}

void ReportItem::inc() {
	++count;
}

bool ReportItem::equ(string& otherType) {
	return type == otherType;
}

void ReportItem::display() {
	cout << type << " appears " << count << " times;\n";
}
