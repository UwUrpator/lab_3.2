#pragma once

#include "Dictionary/Pair.hpp"
#include "../Informator/Informator.hpp"

class PairTester {
public:
    PairTester();

    void TestConstructor1();

    void TestConstructor2();

    void TestGetFirst();

    void TestGetSecond();
};

void PairTester::TestConstructor1() {
    try {
        Pair<string, int>* pair = new Pair<string, int>();

        Informator(
                (pair->GetFirst() == "" && pair->GetSecond() == 0),
                "Success: Pair::Pair(); constructor works correct",
                "Error: Pair::Pair(); constructor works incorrect"
        );
    } catch (...) {
        Informator("Error: Pair::Pair(); constructor works incorrect (Exception)");
    };
}

void PairTester::TestConstructor2() {
    try {
        Pair<string, int>* pair = new Pair<string, int>("Peter", 30);

        Informator(
                (pair->GetFirst() == "Peter" && pair->GetSecond() == 30),
                "Success: Pair::Pair(K first; T second); constructor works correct",
                "Error: Pair::Pair(K first; T second); constructor works incorrect"
        );
    } catch (...) {
        Informator("Error: Pair::Pair(); constructor works incorrect (Exception)");
    };
}

void PairTester::TestGetFirst() {
    try {
        Pair<string, int>* pair = new Pair<string, int>("Peter", 30);

        Informator(
                (pair->GetFirst() == "Peter"),
                "Success: Pair::GetFirst(); returned correct item",
                "Error: Pair::GetFirst(); returned incorrect item"
        );
    } catch (...) {
        Informator("Error: Pair::GetFirst(); returned incorrect item (Exception)");
    };
}

void PairTester::TestGetSecond() {
    try {
        Pair<string, int>* pair = new Pair<string, int>("Peter", 30);

        Informator(
                (pair->GetSecond() == 30),
                "Success: Pair::GetSecond(); returned correct item",
                "Error: Pair::GetSecond(); returned incorrect item"
        );
    } catch (...) {
        Informator("Error: Pair::GetSecond(); returned incorrect item (Exception)");
    };
}

PairTester::PairTester() {
    this->TestConstructor1();

    this->TestConstructor2();

    this->TestGetFirst();

    this->TestGetSecond();
}

