#pragma once

#include <iostream>

using namespace std;

template<class T>
class MultiField {
public:
    T* items;
    MultiField(string message, int size);
};

template<class T>
MultiField<T>::MultiField(string message, int size) {
    this->items = new int[size];

    cout << endl;
    cout << message << " (" << size << " argument(s)):\n";
    for (int i = 0; i < size; ++i) {
        while (!(cin >> items[i])) {
            cin.clear();
            cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input; please re-enter (from wrong symbol).\n";
        }
    }
}
