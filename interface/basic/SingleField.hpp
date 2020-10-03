#pragma once

#include <iostream>

using namespace std;

template<class T>
class SingleField {
public:
   T item;
   SingleField(string message);
};

template<class T>
SingleField<T>::SingleField(string message) {
    while (cout << message << ":\n" && !(cin >> this->item)) {
        cin.clear();
        cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input; please re-enter.\n";
    }
}
