cmake_minimum_required(VERSION 3.15)
project(lab_3.2)

set(CMAKE_CXX_STANDARD 20)

include_directories(source)

set(SOURCE_FILES
        main.cpp
        source/ArraySequence/ArraySequence.hpp
        source/DynamicArray/DynamicArray.hpp
        source/DynamicArray/Optional.hpp
        source/LinearForm/LinearForm.hpp
        source/LinkedList/LinkedList.hpp
        source/LinkedList/Node.hpp
        source/ListSequence/ListSequence.hpp
        source/Sequence/Sequence.hpp
        source/Sorter/ISorter.hpp
        source/Sorter/QuickSorter.hpp
        source/Sorter/ShellSorter.hpp
        source/Set/ISet.hpp
        source/Set/SetSequence.hpp
        source/Set/SetBinaryTree.hpp
        source/BinaryTree/BinaryTree.hpp
        source/BinaryTree/TreeNode.hpp
        tests/Informator/Informator.hpp
        tests/DummyClass/DummyClass.hpp
        tests/DynamicArrayTester/DynamicArrayTester.hpp
        tests/LinkedListTester/LinkedListTester.hpp
        tests/ArraySequenceTester/ArraySequenceTester.hpp
        tests/ListSequenceTester/ListSequenceTester.hpp
        #tests/LinearFormTester/LinearFormTester.hpp
        tests/SorterTester/QuickSorterTester.hpp
        tests/SorterTester/ShellSorterTester.hpp
        tests/SetTester/SetSequenceTester.hpp
        tests/BinaryTreeTester/BinaryTreeTester.hpp
        tests/TestRunner.hpp
        interface/basic/SelectorUI.hpp
        interface/basic/SingleField.hpp
        interface/basic/MultiField.hpp
        interface/UIStarter.hpp
        #interface/LinearFormUI.hpp
        )

add_executable(lab_3.2 ${SOURCE_FILES})