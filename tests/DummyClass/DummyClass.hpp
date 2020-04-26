#pragma once

#include <iostream>

using namespace std;

class DummyClass {
private:
    int field;
public:
    DummyClass();

    DummyClass(int field);

    bool operator==(DummyClass &other);

    bool operator!=(DummyClass &other);

    friend ostream& operator<< (ostream &out, const DummyClass dummyObj);

    int GetField();
};

DummyClass::DummyClass() {
    this->field = 0;
}

DummyClass::DummyClass(int field) {
    this->field = field;
}

bool DummyClass::operator==(DummyClass &other) {
    return this->field == other.GetField();
}

bool DummyClass::operator!=(DummyClass &other) {
    return !(this->field == other.GetField());
}

ostream &operator<<(ostream &out, DummyClass dummyObj) {
    out << dummyObj.field;

    return out;
}

int DummyClass::GetField() {
    return this->field;
}


