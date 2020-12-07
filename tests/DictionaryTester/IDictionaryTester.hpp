#pragma once

#include <iostream>
#include "string"

#include "../source/Dictionary/IDictionary.hpp"
#include "../Informator/Informator.hpp"

template<class T>
class IDictionaryTester {
public:
    IDictionaryTester<T>(string name);

private:
    string name;

    void TestCount();

    void TestCapacity();

    void TestGet();

    //void TestGetKeyByIndex();

    void TestContainsKey();

    void TestAdd();

    void TestRemove();

    void TestChange();

    void TestGetKeys();
};

template<class T>
IDictionaryTester<T>::IDictionaryTester(string name) {
    this->name = name;

    this->TestCount();
    this->TestCapacity();
    this->TestGet();
    //this->TestGetKeyByIndex();
    this->TestContainsKey();
    this->TestAdd();
    this->TestRemove();
    this->TestChange();
    this->TestGetKeys();
}

template<class T>
void IDictionaryTester<T>::TestCount() {
    IDictionary<string, int>* dict = new T(3);

    dict->Add("Peter", 30);

    Informator(
        (dict->Count() == 1),
        "Success: int " + this->name + "::Count(); Correct count",
        "Error: int " + this->name + "::Count(); Incorrect count"
    );
}

template<class T>
void IDictionaryTester<T>::TestCapacity() {
    IDictionary<string, int>* dict = new T(4);

    Informator(
            (dict->Capacity() == 4),
            "Success: int " + this->name + "::Capacity(); Correct capacity",
            "Error: int " + this->name + "::Capacity(); Incorrect capacity"
    );
}

template<class T>
void IDictionaryTester<T>::TestGet() {
    IDictionary<string, int>* dict = new T(3);

    dict->Add("Peter", 30);
    dict->Add("Jack", 28);
    dict->Add("Bob", 32);

    try {
        dict->Get("Bill");

        Informator("Error: T " + this->name + "::Get(); Exception was not thrown (there is no such key)");
    } catch (...) {
        Informator("Success: T " + this->name + "::Get(); Exception was thrown (there is no such key)");
    }

    Informator(
            (dict->Get("Bob") == 32),
            "Success: T " + this->name + "::Get(); Correct item was gotten",
            "Error: T " + this->name + "::Get(); Incorrect item was gotten"
    );
}

template<class T>
void IDictionaryTester<T>::TestContainsKey() {
    IDictionary<string, int>* dict = new T(3);

    dict->Add("Peter", 30);
    dict->Add("Jack", 28);

    Informator(
            (dict->ContainsKey("Jack")),
            "Success: bool " + this->name + "::ContainsKey(); Such item is contained",
            "Error: bool " + this->name + "::ContainsKey(); Such item is contained, but function returns False"
    );

    Informator(
            (!dict->ContainsKey("Bill")),
            "Success: bool " + this->name + "::ContainsKey(); Such item is not contained",
            "Error: bool " + this->name + "::ContainsKey(); Such item is not contained, but function returns True"
    );
}

template<class T>
void IDictionaryTester<T>::TestAdd() {
    IDictionary<string, int>* dict = new T(3);

    dict->Add("Peter", 30);

    Informator(
            (
                dict->ContainsKey("Peter") &&
                dict->Get("Peter") == 30 &&
                dict->Capacity() == 3 &&
                dict->Count() == 1
            ),
            "Success: void " + this->name + "::Add(); Added correctly",
            "Error: void " + this->name + "::Add(); Added incorrectly"
    );
}

template<class T>
void IDictionaryTester<T>::TestRemove() {
    IDictionary<string, int>* dict = new T(3);

    dict->Add("Peter", 30);
    dict->Add("Jack", 28);
    dict->Add("Bob", 32);
    dict->Remove("Bob");

    Informator(
            (
                    !dict->ContainsKey("Bob") &&
                    dict->Capacity() == 3 &&
                    dict->Count() == 2
            ),
            "Success: void " + this->name + "::Remove(); Removed correctly",
            "Error: void " + this->name + "::Remove(); Removed incorrectly"
    );
}

template<class T>
void IDictionaryTester<T>::TestChange() {
    IDictionary<string, int>* dict = new T(3);

    dict->Add("Peter", 30);
    dict->Change("Peter", dict->Get("Peter") + 1);

    Informator(
            (
                    dict->ContainsKey("Peter") &&
                    dict->Capacity() == 3 &&
                    dict->Count() == 1 &&
                    dict->Get("Peter") == 31
            ),
            "Success: void " + this->name + "::Change(); Changed correctly",
            "Error: void " + this->name + "::Change(); Changed incorrectly"
    );
}

template<class T>
void IDictionaryTester<T>::TestGetKeys() {
    IDictionary<string, int>* dict = new T(3);

    dict->Add("Peter", 30);
    dict->Add("Jack", 28);
    dict->Add("Bob", 32);

    Sequence<string>* resultSeq = dict->GetKeys();

    Informator(
            (
                (
                        resultSeq->Get(0) == "Peter" &&
                        resultSeq->Get(1) == "Jack" &&
                        resultSeq->Get(2) == "Bob"
                ) ||
                (
                        resultSeq->Get(0) == "Jack" &&
                        resultSeq->Get(1) == "Peter" &&
                        resultSeq->Get(2) == "Bob"
                )
            ),
            "Success: Sequence<K>* " + this->name + "::GetKeys(); Correct keys",
            "Error: Sequence<K>* " + this->name + "::GetKeys(); Incorrect kyes"
    );
}

