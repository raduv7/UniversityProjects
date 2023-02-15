#pragma once
#include <assert.h>
#include "service.h"

void testDomain() {
	BundleElement toTestElem0;
	BundleElement toTestElem1("","","");
	BundleElement toTestElem2("name", "type", "descr");
	BundleElement toTestElem3(toTestElem2);
	assert(toTestElem3.getName() == "name");
	toTestElem0 = toTestElem3;
	assert(toTestElem0.getType() == "type");
	assert(toTestElem0 == toTestElem2);
	assert(toTestElem0.getDescr() == toTestElem2.getDescr());
}

void testRepository() {}

void testServiceField(const string& toTestField) {
	assert(toTestField[0] >= 'A' && toTestField[0] <= 'Z');
	assert(toTestField.length() >= 3 && toTestField.length() <= 12);
	int i;
	for (i = 1; i < toTestField.length(); ++i) {
		assert(toTestField[i] >= 'a' && toTestField[i] <= 'z');
	}
}

void testService() {
	Repository testRepo("testdata.txt");
	Service testSrv(testRepo);
	testSrv.clear();
	assert(testSrv.size() == 0);
	assert(testSrv.add("name", "type", "descr") == true);
	assert(testSrv.add("name", "type", "descr") == false);
	assert(testSrv.del("name", "type", "descr") == true);
	assert(testSrv.del("name", "type", "descr") == false);
	testSrv.generate();
	assert(testSrv.size() > 0);
	vector <BundleElement> testV = testSrv.getAll();
	testServiceField(testV[0].getName());
	testServiceField(testV[0].getType());
	testServiceField(testV[0].getDescr());
}


void testAll() {
	testDomain();
	testRepository();
	testService();
}
