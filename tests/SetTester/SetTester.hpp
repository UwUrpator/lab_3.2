#pragma once

#include <iostream>

#include "../source/Set/SetSequence.hpp"
#include "../source/Set/SetBinaryTree.hpp"
#include "../tests/SetTester/ISetTester.hpp"
#include "../Informator/Informator.hpp"

class SetTester {
public:
    SetTester();
};

SetTester::SetTester() {
    ISetTester<SetSequence<int>>("SetSequence");
    ISetTester<SetBinaryTree<int>>("SetBinaryTree");
}
