//
// Created by Radu on 3/29/2022.
//

#include <iostream>
#include "tests.h"
#include "activityService.h"
//#include "myVectorIterator.h"

#include <cassert>

void testDomain() {
    Activity toTestActivity1("munte;d12;sport;12");
    Activity toTestActivity2("munte;d12;sport;12");
    Activity toTestActivity3("muntee;d12;sport;122");
    const Activity& toTestActivity4(toTestActivity3);
    assert(toTestActivity1 == toTestActivity2);
    assert(toTestActivity3 == toTestActivity4);
    assert((toTestActivity1 == toTestActivity4) == false);
}

void testRepo() {
    ActivityRepository toTestRepo("");
    // toTestRepo.~ActivityRepository();
}

void testSrv() {
    printf("Testing service, sir!\n");

    ActivityRepository toTestRepo("datatest.txt");
    printf("Testing service creator, sir!\n");
    ActivityService toTestSrv(toTestRepo);
    string toTestString;

    printf("Service creator tests passed, sir!\n");

    toTestSrv.undo();
    assert(toTestSrv.add("bauta;d13;familie;13") == true);
    assert(toTestSrv.add("bauta;d13;sport;13") == false);
    assert(toTestSrv.add("altabauta;d13 sport;13") == false);
    assert(toTestSrv.add("bau;ta;d13;sport;13") == false);
    assert(toTestSrv.add("bauta2;d13;familie;13") == true);
    assert(toTestSrv.findActivity("bauta", toTestString) == true);
    assert(toTestString == "bauta;d13;familie;13\n");

    printf("Service add tests passed, sir!\n");

    assert(toTestSrv.update("bauta;d13;societate;13") == true);
    assert(toTestSrv.update("bauta;d13;societate;13") == true);
    assert(toTestSrv.update("altabauta;d13;societate;13") == false);
    assert(toTestSrv.findActivity("bauta", toTestString) == true);
    assert(toTestString == "bauta;d13;societate;13\n");

    printf("Service update tests passed, sir!\n");

    assert(toTestSrv.del("bauta") == true);
    assert(toTestSrv.del("bauta2") == true);
    assert(toTestSrv.findActivity("bauta", toTestString) == false);
    assert(toTestString.empty());

    printf("Service del tests passed, sir!\n");

    toTestSrv.getAll("", "");
    toTestSrv.getAll("", "societate");
    toTestSrv.getAll("d7", "");
    toTestSrv.getAll("d11", "familie");
    toTestSrv.getAll("d7", "familie");

    printf("Service show tests passed, sir!\n");

    toTestSrv.sort("asc", "name");
    toTestSrv.sort("asc", "description");
    toTestSrv.sort("asc", "type");
    toTestSrv.sort("asc", "duration");
    toTestSrv.sort("asc", "others");
    toTestSrv.sort("desc", "name");
    toTestSrv.sort("desc", "description");
    toTestSrv.sort("desc", "type");
    toTestSrv.sort("desc", "duration");
    toTestSrv.sort("desc", "others");
    toTestSrv.sort("up", "type");

    printf("Service sort tests passed, sir!\n");

    assert(toTestSrv.generateByName("a;b") == false);
    assert(toTestSrv.generateByName("") == false);
    assert(toTestSrv.generateAll("-1") == false);

    assert(toTestSrv.add("bauta2;d13;familie;13") == true);
    assert(toTestSrv.update("bauta2;d1;familie;13") == true);
    assert(toTestSrv.del("bauta2") == true);
    assert(toTestSrv.findActivity("bauta2", toTestString) == false);
    toTestSrv.undo();
    assert(toTestSrv.findActivity("bauta2", toTestString) == true);
    toTestSrv.undo();
    assert(toTestSrv.findActivity("bauta2", toTestString) == true);
    toTestSrv.undo();
    assert(toTestSrv.findActivity("bauta2", toTestString) == false);

    // toTestSrv.destructor();

    toTestSrv.reportTypes();

    printf("Service destructor tests passed, sir!\n");

}

void testSrv2() {

    ActivityRepository toTestRepo("datatest2.txt");
    printf("Testing service creator, sir!\n");
    ActivityService toTestSrv(toTestRepo);
    toTestSrv.delAll();
    vector <Activity> toTestAll;
    toTestAll = toTestSrv.getAll("", "");
    assert(toTestAll.size() == 0);

    toTestSrv.generateByName("gen1");
    toTestAll = toTestSrv.getAll("", "");
    assert(toTestAll.size() == 1);
    toTestSrv.generateByName("gen2");
    toTestAll = toTestSrv.getAll("", "");
    assert(toTestAll.size() == 2);

    toTestSrv.generateAll("7");
    toTestAll = toTestSrv.getAll("", "");
    assert(toTestAll.size() == 9);

}
/*
void testIterator() {
    MyVector testVector;
    Activity newActivity1("ping pong; d7; sport; 7");
    testVector.push_back(newActivity1);
    Activity newActivity2("ping pong; d8; sport; 7");
    testVector.push_back(newActivity2);
    Activity newActivity3("ping pong; d9; sport; 7");
    testVector.push_back(newActivity3);
    MyVectorIterator testIterator(testVector);
    assert(testIterator.valid() == true);
    cout << "check0\n";
    testIterator.value();
    cout << "check1\n";
    testIterator.next();
    testIterator.begin();
    assert(testIterator.valid() == true);
    testIterator.next();
    testIterator.next();
    testIterator.value();
    cout << "check2\n";
    assert(testIterator.valid() == true);
    testIterator.next();
    try {
        testIterator.value();
    }
    catch (int error) {
        cout << error;
    }
    cout << "check3\n";
    try {
        testIterator.next();
    }
    catch (int error) {
        cout << error;
    }
    assert(testIterator.valid() == false);
    cout << "check4\n";
    testIterator.begin();
    assert(testIterator.valid() == true);
    testIterator.next();
    testIterator.value();
    assert(testIterator.valid() == true);
    cout << "check5\n";
    return;
}*/

void testAll() {
    testDomain();
    printf("Domain tests passed, sir!\n");
    testRepo();
    printf("Repository tests passed, sir!\n");
    testSrv();
    printf("Service first tests passed, sir!\n");
    testSrv2();
    printf("Service second tests passed, sir!\n");
    //testIterator();
    printf("Iterator tests passed, sir!\n");

}


/**

ski;d1;sport;1
ping pong;d7;sport;7
parasutism;d2;sport;2
munte;d12;sport;12
handbal;d5;sport;5
basket;d3;sport;3
petreceri;d8;societate;8
dateuri;d9;societate;9
bere cu baietii;d10;societate;10
remi cu ai mei;d11;familie;11

*/