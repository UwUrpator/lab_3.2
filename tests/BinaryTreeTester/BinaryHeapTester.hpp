#pragma once

#include <iostream>
#include <string>

#include "../source/BinaryTree/BinaryHeap.hpp"

using namespace std;

class BinaryHeapTester {
public:
    BinaryHeapTester();
    void testInsert();
    void testToString();
    void testRemote();
    void testSearch();
};

BinaryHeapTester::BinaryHeapTester() {
    testInsert();
    testToString();
    testRemote();
    testSearch();
}

void BinaryHeapTester::testInsert() {
    BinaryHeap<int>* binaryHeap = new BinaryHeap<int>();

    binaryHeap->insert(16);
    binaryHeap->insert(11);
    binaryHeap->insert(9);
    binaryHeap->insert(10);
    binaryHeap->insert(5);
    binaryHeap->insert(6);
    binaryHeap->insert(8);
    binaryHeap->insert(1);
    binaryHeap->insert(2);
    binaryHeap->insert(4);

    string output = binaryHeap->toString();

    if (output != "{16}({11}({10}({1})[{2}])[{5}({4})])[{9}({6})[{8}]]") {
        cout << "Error: BinaryHeap::insert; uncorrected heap after insertions" << endl;
        return;
    }

    cout << "Correct: BinaryHeap::insert; correct heap after insertions" << endl;

    delete binaryHeap;
}

void BinaryHeapTester::testToString() {
    BinaryHeap<int>* binaryHeap = new BinaryHeap<int>();

    binaryHeap->insert(16);
    binaryHeap->insert(11);
    binaryHeap->insert(9);
    binaryHeap->insert(10);
    binaryHeap->insert(5);
    binaryHeap->insert(6);
    binaryHeap->insert(8);
    binaryHeap->insert(1);
    binaryHeap->insert(2);
    binaryHeap->insert(4);

    string output = binaryHeap->toString("LKR");

    if (output != "((({1}){10}[{2}]){11}[({4}){5}]){16}[({6}){9}[{8}]]") {
        cout << "Error: BinaryHeap::toString; uncorrected LKR string" << endl;
        return;
    }

    cout << "Correct: BinaryHeap::toString; correct LKR string" << endl;

    delete binaryHeap;
}

void BinaryHeapTester::testRemote() {
    BinaryHeap<int>* binaryHeap = new BinaryHeap<int>();

    binaryHeap->insert(16);
    binaryHeap->insert(11);
    binaryHeap->insert(9);
    binaryHeap->insert(10);
    binaryHeap->insert(5);
    binaryHeap->insert(6);
    binaryHeap->insert(8);
    binaryHeap->insert(1);
    binaryHeap->insert(2);
    binaryHeap->insert(4);

    binaryHeap->remove(0);

    string output = binaryHeap->toString();

    if (output != "{11}({10}({4}({1})[{2}])[{5}])[{9}({6})[{8}]]") {
        cout << "Error: BinaryHeap::remove; node wasnt correctly removed" << endl;
        return;
    }

    cout << "Correct: BinaryHeap::remove; node was correctly removed" << endl;

    delete binaryHeap;
}

void BinaryHeapTester::testSearch() {
    BinaryHeap<int>* binaryHeap = new BinaryHeap<int>();

    binaryHeap->insert(16);
    binaryHeap->insert(11);
    binaryHeap->insert(9);
    binaryHeap->insert(10);
    binaryHeap->insert(5);
    binaryHeap->insert(6);
    binaryHeap->insert(8);
    binaryHeap->insert(1);
    binaryHeap->insert(2);
    binaryHeap->insert(4);

    int result = binaryHeap->search(4);

    if (result != 5) {
        cout << "Error: BinaryHeap::search; uncorrected node was found" << endl;
        return;
    }

    cout << "Correct: BinaryHeap::search; node was correctly found" << endl;

    delete binaryHeap;
}
