cmake_minimum_required(VERSION 3.15)
project(lab_2_my)

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
        tests/DummyClass/DummyClass.hpp
        tests/DynamicArrayTester/DynamicArrayTester.hpp
        tests/LinkedListTester/LinkedListTester.hpp
        tests/ArraySequenceTester/ArraySequenceTester.hpp
        tests/ListSequenceTester/ListSequenceTester.hpp
        tests/LinearFormTester/LinearFormTester.hpp
        tests/TestRunner.hpp
        interface/UIStarter.hpp
        interface/LinearFormUI.hpp
        )

add_executable(lab_2 ${SOURCE_FILES})