#include "tests.h"
#include <cassert>

void testRepo() {
	bool ok;
	try {
		Repository repo("datatest1.txt");
		ok = false;
	} 
	catch(...) {
		ok = true;
	}
	assert(ok);
	try {
		Repository repo("datatest2.txt");
		ok = false;
	}
	catch (...) {
		ok = true;
	}
	assert(ok);

	Repository repo("datatest.txt");
	assert(repo.getAll().size() == 14);
}

void testSrv() {
	Repository repo("datatest.txt");
	Service srv(&repo);
	assert(srv.getAll().size() == 14);
	assert(srv.getAllTypes().size() == 3);

	vector <string> types(srv.getAllTypes());
	int sum = 0;
	for (auto type : types) {
		sum += srv.prodCounter(type);
	}
	assert(sum == 14);

	if (true) {
		string fields[4] = {"7","7.0","type","name"};
		assert(!srv.addProd(fields).empty());
	}

	if (true) {
		string fields[4] = {"-1","7.0","type","name"};
		assert(!srv.addProd(fields).empty());
	}

	if (true) {
		string fields[4] = {"id","7.0","type","name"};
		assert(!srv.addProd(fields).empty());
	}

	if (true) {
		string fields[4] = {"17","-1","type","name"};
		assert(!srv.addProd(fields).empty());
	}

	if (true) {
		string fields[4] = {"17","0.3","type","name"};
		assert(!srv.addProd(fields).empty());
	}

	if (true) {
		string fields[4] = {"17","101","type","name"};
		assert(!srv.addProd(fields).empty());
	}

	if (true) {
		string fields[4] = {"17","price","type","name"};
		assert(!srv.addProd(fields).empty());
	}

	if (true) {
		string fields[4] = {"17","17","","name"};
		assert(!srv.addProd(fields).empty());
	}

	if (true) {
		string fields[4] = {"17","17","ty;pe","name"};
		assert(!srv.addProd(fields).empty());
	}

	if (true) {
		string fields[4] = {"17","17","type",""};
		assert(!srv.addProd(fields).empty());
	}

	if (true) {
		string fields[4] = {"17","17","type","na;me"};
		assert(!srv.addProd(fields).empty());
	}

	if (true) {
		string fields[4] = {"17","17","type","name"};
		assert(srv.addProd(fields).empty());
	}
	assert(srv.getAll().size() == 15);

}

void testAll() {
	testRepo();
	testSrv();
}