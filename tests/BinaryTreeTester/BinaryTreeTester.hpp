#pragma once

#include <iostream>
#include <string>

#include "../source/BinaryTree/BinaryTree.hpp"
#include "../Informator/Informator.hpp"

using namespace std;

int mult2(int a) {
    return a * 2;
}

int add1(int a) {
    return a + 1;
}

int sum(int a, int b) {
    return a + b;
}

bool isEven(int a) {
    return abs(a % 2) == 0;
}

string concatIntString(int a, string b) {
    return b + to_string(a) ;
}

class BinaryTreeTester {
public:
    BinaryTreeTester();

    void testInsert();

    void testToString();

    void testSearch();

    void testDeleteTreeNode();

    void testMapOneType();

    void testMapTwoTypes();

    void testReduceOneType();

    void testReduceTwoTypes();

    void testWhere();

    void testThreat();

    void testGetSubTree();

    void testContainsSubTree();

    void testCount();
};

BinaryTreeTester::BinaryTreeTester() {
    testInsert();
    testToString();
    testSearch();
    testDeleteTreeNode();
    testMapOneType();
    testMapTwoTypes();
    testReduceOneType();
    testReduceTwoTypes();
    testWhere();
    testThreat();
    testGetSubTree();
    testContainsSubTree();
    testCount();
}

void BinaryTreeTester::testInsert() {
    BinaryTree<int>* binaryTree = new BinaryTree<int>();

    binaryTree->Insert(1);
    binaryTree->Insert(2);
    binaryTree->Insert(3);
    binaryTree->Insert(1);

    string output = binaryTree->ToString("KLR");

    if (output != "{1}({1})[{2}[{3}]]") {
        cout << "Error: BinaryTree::Insert; uncorrected tree after Insertions" << endl;
        return;
    }

    cout << "Success: BinaryTree::Insert; correct tree after Insertions" << endl;

    delete binaryTree;
}

void BinaryTreeTester::testToString() {
    BinaryTree<int>* binaryTree = new BinaryTree<int>();

    binaryTree->Insert(8);
    binaryTree->Insert(3);
    binaryTree->Insert(10);
    binaryTree->Insert(1);
    binaryTree->Insert(6);
    binaryTree->Insert(14);
    binaryTree->Insert(4);
    binaryTree->Insert(7);
    binaryTree->Insert(13);

    string output = binaryTree->ToString("KLR");

    if (output != "{8}({3}({1})[{6}({4})[{7}]])[{10}[{14}({13})]]") {
        cout << "Error: BinaryTree::ToString; uncorrected string" << endl;
    }

    cout << "Success: BinaryTree::ToString; correct string" << endl;

    delete binaryTree;
}


void BinaryTreeTester::testSearch() {
    BinaryTree<int>* binaryTree = new BinaryTree<int>();

    binaryTree->Insert(8);
    binaryTree->Insert(3);
    binaryTree->Insert(10);
    binaryTree->Insert(1);
    binaryTree->Insert(6);
    binaryTree->Insert(14);
    binaryTree->Insert(4);
    binaryTree->Insert(7);
    binaryTree->Insert(13);

    TreeNode<int>* foundTreeNode = binaryTree->Search(3);

    if (*foundTreeNode->value != 3) {
        cout << "Error: BinaryTree::search; wrong node was found" << endl;
        return;
    }

    cout << "Success: BinaryTree::search; correct node was found" << endl;

    delete binaryTree;
}

void BinaryTreeTester::testDeleteTreeNode() {
    BinaryTree<int> *binaryTree = new BinaryTree<int>();

    binaryTree->Insert(8);
    binaryTree->Insert(3);
    binaryTree->Insert(10);
    binaryTree->Insert(1);
    binaryTree->Insert(6);
    binaryTree->Insert(14);
    binaryTree->Insert(4);
    binaryTree->Insert(7);
    binaryTree->Insert(13);

    binaryTree->DeleteTreeNode(8);
    string output = binaryTree->ToString("KLR");

    if (output != "{10}({3}({1})[{6}({4})[{7}]])[{14}({13})]") {
        cout << "Error: BinaryTree::delete; delete operation doesnt work" << endl;
        return;
    }

    cout << "Success: BinaryTree::delete; delete operation works correctly" << endl;

    delete binaryTree;
}

void BinaryTreeTester::testMapOneType() {
    BinaryTree<int>* binaryTree = new BinaryTree<int>();

    binaryTree->Insert(8);
    binaryTree->Insert(3);
    binaryTree->Insert(10);
    binaryTree->Insert(1);
    binaryTree->Insert(6);
    binaryTree->Insert(14);
    binaryTree->Insert(4);
    binaryTree->Insert(7);
    binaryTree->Insert(13);

    BinaryTree<int>* newBinaryTree = binaryTree->Map(mult2);

    binaryTree->Insert(1);
    newBinaryTree->Insert(100);

    string output = newBinaryTree->ToString("KLR");

    if (output != "{16}({6}({2})[{12}({8})[{14}]])[{20}[{28}({26})[{100}]]]") {
        cout << "Error: BinaryTree::Map; Map operation with one type doesnt work" << endl;
        return;
    }

    cout << "Success: BinaryTree::Map; Map operation with one type works correctly" << endl;

    delete binaryTree;
    delete newBinaryTree;
}

void BinaryTreeTester::testMapTwoTypes() {
    BinaryTree<int>* binaryTree = new BinaryTree<int>();

    binaryTree->Insert(8);
    binaryTree->Insert(3);
    binaryTree->Insert(10);
    binaryTree->Insert(1);
    binaryTree->Insert(6);
    binaryTree->Insert(14);
    binaryTree->Insert(4);
    binaryTree->Insert(7);
    binaryTree->Insert(13);

    BinaryTree<bool>* newBinaryTree = binaryTree->Map(isEven);

    binaryTree->Insert(1);

    string output = newBinaryTree->ToString("KLR");

    if (output != "{1}({0}({0}({0}({0})))[{1}({1}({1}({1})))])") {
        cout << "Error: BinaryTree::Map; Map operation with two types doesnt work" << endl;
        return;
    }

    cout << "Success: BinaryTree::Map; Map operation with two types works correctly" << endl;

    delete binaryTree;
    delete newBinaryTree;
}

void BinaryTreeTester::testReduceOneType() {
    BinaryTree<int>* binaryTree = new BinaryTree<int>();

    binaryTree->Insert(8);
    binaryTree->Insert(3);
    binaryTree->Insert(10);
    binaryTree->Insert(1);
    binaryTree->Insert(6);
    binaryTree->Insert(14);
    binaryTree->Insert(4);
    binaryTree->Insert(7);
    binaryTree->Insert(13);

    int result = binaryTree->Reduce(sum);

    if (result != 66) {
        cout << "Error: BinaryTree::Reduce; Reduce operation with one type doesnt work" << endl;
        return;
    }

    cout << "Success: BinaryTree::Reduce; Reduce operation with one type works correctly" << endl;

    delete binaryTree;
}

void BinaryTreeTester::testReduceTwoTypes() {
    BinaryTree<int>* binaryTree = new BinaryTree<int>();

    binaryTree->Insert(8);
    binaryTree->Insert(3);
    binaryTree->Insert(10);
    binaryTree->Insert(1);
    binaryTree->Insert(6);
    binaryTree->Insert(14);
    binaryTree->Insert(4);
    binaryTree->Insert(7);
    binaryTree->Insert(13);

    string result = binaryTree->Reduce(concatIntString);

    if (result != "831647101413") {
        cout << "Error: BinaryTree::Reduce; Reduce operation with two types doesnt work" << endl;
        return;
    }

    cout << "Success: BinaryTree::Reduce; Reduce operation with two types works correctly" << endl;

    delete binaryTree;
}

void BinaryTreeTester::testWhere() {
    BinaryTree<int>* binaryTree = new BinaryTree<int>();

    binaryTree->Insert(8);
    binaryTree->Insert(3);
    binaryTree->Insert(10);
    binaryTree->Insert(1);
    binaryTree->Insert(6);
    binaryTree->Insert(14);
    binaryTree->Insert(4);
    binaryTree->Insert(7);
    binaryTree->Insert(13);

    BinaryTree<int>* newBinaryTree = binaryTree->Where(isEven);

    binaryTree->Insert(1);
    newBinaryTree->Insert(100);

    string output = newBinaryTree->ToString();

    if (output != "{8}({6}({4}))[{10}[{14}[{100}]]]") {
        cout << "Error: BinaryTree::Where; Where operation doesnt work" << endl;
        return;
    }

    cout << "Success: BinaryTree::Where; Where operation works correctly" << endl;

    delete binaryTree;
    delete newBinaryTree;
}

void BinaryTreeTester::testThreat() {
    BinaryTree<int>* binaryTree = new BinaryTree<int>();

    binaryTree->Insert(8);
    binaryTree->Insert(3);
    binaryTree->Insert(10);
    binaryTree->Insert(1);
    binaryTree->Insert(6);
    binaryTree->Insert(14);
    binaryTree->Insert(4);
    binaryTree->Insert(7);
    binaryTree->Insert(13);

    LinkedList<TreeNode<int>*>* threatList = binaryTree->Thread("LKR");

    stringstream strs;

    for (int i = 0; i < 9; i++) {
        strs << *threatList->Get(i)->value << " ";
    }

    if (strs.str() != "1 3 4 6 7 8 10 13 14 ") {
        cout << "Error: BinaryTree::threat; wrong Threaded tree" << endl;
        return;
    }

    cout << "Success: BinaryTree::threat; correct Threaded tree" << endl;

    delete binaryTree;
}

void BinaryTreeTester::testGetSubTree() {
    BinaryTree<int>* binaryTree = new BinaryTree<int>();

    binaryTree->Insert(8);
    binaryTree->Insert(3);
    binaryTree->Insert(10);
    binaryTree->Insert(1);
    binaryTree->Insert(6);
    binaryTree->Insert(14);
    binaryTree->Insert(4);
    binaryTree->Insert(7);
    binaryTree->Insert(13);

    BinaryTree<int>* newBinaryTree = binaryTree->GetSubTree(8);

    string output = newBinaryTree->ToString();

    if (output != "{8}({3}({1})[{6}({4})[{7}]])[{10}[{14}({13})]]") {
        cout << "Error: BinaryTree::GetSubTree; wrong sub tree" << endl;
        return;
    }

    cout << "Success: BinaryTree::GetSubTree; correct sub tree" << endl;

    delete binaryTree;
    delete newBinaryTree;
}

void BinaryTreeTester::testContainsSubTree() {
    BinaryTree<int>* binaryTree = new BinaryTree<int>();

    binaryTree->Insert(8);
    binaryTree->Insert(3);
    binaryTree->Insert(10);
    binaryTree->Insert(1);
    binaryTree->Insert(6);
    binaryTree->Insert(14);
    binaryTree->Insert(4);
    binaryTree->Insert(7);
    binaryTree->Insert(13);

    BinaryTree<int>* newBinaryTree = new BinaryTree<int>();

    newBinaryTree->Insert(6);
    newBinaryTree->Insert(4);
    newBinaryTree->Insert(7);

    if (!binaryTree->ContainsSubTree(newBinaryTree)) {
        cout << "Error: BinaryTree::ContainsSubTree; it should contain" << endl;
        return;
    }

    cout << "Success: BinaryTree::GetSubTree; it contains" << endl;

    delete binaryTree;
    delete newBinaryTree;
}

void BinaryTreeTester::testCount() {
    BinaryTree<int>* binaryTree = new BinaryTree<int>();

    binaryTree->Insert(8);
    binaryTree->Insert(3);
    binaryTree->Insert(10);
    binaryTree->Insert(1);
    binaryTree->Insert(6);
    binaryTree->Insert(14);
    binaryTree->Insert(4);
    binaryTree->Insert(7);
    binaryTree->Insert(13);

    Informator(
        (binaryTree->Count() == 9),
        "Success: BinaryTree::Count(); correct amount of nodes",
        "Error: BinaryTree::Count(); incorrect amount of nodes"
    );
}
