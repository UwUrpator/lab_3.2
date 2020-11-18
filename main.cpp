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
    //UIStarter();
    Cat cat1 = Cat("Barcik", 2);
    Cat cat2 = Cat("Vacya", 12);
    Cat cat3 = Cat("Ivan", 50);
    Cat cat4 = Cat("Barcik", 3);

    Cat* catsArr = new Cat[4];
    catsArr[0] = cat1;
    catsArr[1] = cat2;
    catsArr[2] = cat3;
    catsArr[3] = cat4;

    ArraySequence<Cat>* cats = new ArraySequence<Cat>(catsArr, 4);

    cout << cats->GetLength() << endl;

    cats->RemoveAll(&isOld);

    cout << cats->GetLength() << endl;

    return 0;
}
