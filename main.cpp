#include <iostream>
#include "interface/UIStarter.hpp"

#include "source/Sorter/ShellSorter.hpp"
#include "source/ArraySequence/ArraySequence.hpp"

class Cat {
public:
    int age;
    string name;

    Cat() {
        this->age = 0;
        this->name = "No name";
    }

    Cat(string name, int age) {
        this->age = age;
        this->name = name;
    }

    bool operator==(Cat &other){
        return (this->name == other.name && this->age == other.age);
    }

    bool operator!=(Cat &other){
        return !(this->name == other.name && this->age == other.age);
    }

    void SayHello() {
        cout << "Meow!";
    }
};

bool isOld(Cat cat) {
    return cat.age > 10;
}

using namespace std;

int main() {
    UIStarter();

    return 0;
}
