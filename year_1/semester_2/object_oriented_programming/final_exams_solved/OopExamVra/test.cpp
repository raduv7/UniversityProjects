#include "tests.h"
#include "service.h"
#include <cassert>

void testRepo() {
	;
}

void testService() {
	Repository trepo("datatest.txt");
	Service tsrv(trepo);
	vector <Game> tv = tsrv.getAll();
	assert(tv[0].getSquares() == "X-OXO-XOO");
	assert(tv[1].getSquares() == "--------X");
	assert(tsrv[0].getDim() == 3);
	assert(tsrv[0].getStg() == "Terminat");
	assert(tsrv[0].getId() == 0);
	assert(tsrv[0].getPlayer() == 'X');
	assert(tsrv.size() == 5);

	tsrv.add("5","XXXXXOOOOO-----XXXXXOOOOO","X");
	assert(tsrv.size() == 6);
	tsrv.act(5,"5","XXXXXOOOOO-----XXXXXOOOOO","X","Terminat");
	assert(tsrv.size() == 6);
	tsrv.played(5,2,0);
	string correctAns = tsrv[5].getSquares();
	assert(tsrv[5].getSquares() == "XXXXXOOOOOX----XXXXXOOOOO");
	assert(tsrv[5].getPlayer() == 'O');
	trepo.del(5);
}

void testAll() {
	testRepo();
	testService();
}