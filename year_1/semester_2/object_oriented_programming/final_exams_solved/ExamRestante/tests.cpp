#include "tests.h"

void testDomain() {
	string testFields[4] = {"17","1.7","radu","radu"};
	Prod* testProd = new Prod(testFields);
	assert(testProd->getId() == 17);
	assert(testProd->getPrice() == 1.7);
	assert(testProd->getName() == "radu");
	assert(testProd->getType() == "radu");
	assert(testProd->toString() == "17;1.700000;radu;radu\n");
}
void testRepo() {
	bool ok;
	try {
		Repo repo("datatest1.txt");
		ok = false;
	}
	catch (...) {
		ok = true;
	}
	assert(ok);
	try {
		Repo repo("datatest2.txt");
		ok = false;
	}
	catch (...) {
		ok = true;
	}
	assert(ok);
	try {
		Repo repo("datatest3.txt");
		ok = false;
	}
	catch (...) {
		ok = true;
	}
	assert(ok);
}
void testService() {
	Repo testRepo("datatest.txt");
	Service srv(&testRepo);
	assert(srv.getAll().size() == 12);
	assert(srv.getTypes().size() == 3);
	vector<string> ttypes(srv.getTypes());
	int sum = 0;
	for (auto ttype : ttypes) {
		sum += srv.countType(ttype);
	}
	assert(sum == srv.getAll().size());

	bool ok;

	string testf0[4] = {"12","1.7","radu","radu"};
	assert(!srv.add(testf0).empty());
	
	string testf1[4] = {"17","0.7","radu","radu"};
	assert(!srv.add(testf1).empty());

	string testf2[4] = {"17","-1.7","radu","radu"};
	assert(!srv.add(testf2).empty());
	
	string testf3[4] = {"17","170","radu","radu"};
	assert(!srv.add(testf3).empty());
	
	string testf4[4] = {"17","17","","radu"};
	assert(!srv.add(testf4).empty());
	
	string testf5[4] = {"17","17","ra;du","radu"};
	assert(!srv.add(testf5).empty());
	
	string testf6[4] = {"17","17","radu","ra;du"};
	assert(!srv.add(testf6).empty());
	
	string testf7[4] = {"17","17","radu","radu"};
	assert(srv.add(testf7).empty());

	assert(srv.getAll().size() == 13);
	assert(srv.getTypes().size() == 4);
	ttypes = srv.getTypes();
	sum = 0;
	for (auto ttype : ttypes) {
		sum += srv.countType(ttype);
	}
	assert(sum == srv.getAll().size());

}

class TestObserver : public Observer {
private:
	Observable* srv;
public:
	bool ok;
	TestObserver(Observable*newSrv) : srv(newSrv) { srv->addObs(this), ok = false; };
	~TestObserver() { srv->delObs(this); }

	void update(int reqId = 0) override {
		ok = !ok;
	}
};

void testObserver() {
	Observable obsBig;
	TestObserver obs(&obsBig);
	assert(!obs.ok);
	obsBig.notify();
	assert(obs.ok);
	obsBig.notify();
	assert(!obs.ok);
}


void testAll() {
	testDomain();
	testRepo();
	testService();
	testObserver();
}