#pragma once

#include "UIStarter.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

template<class T>
class LinearFormUI {
private:
    int operation;

    LinearForm<T> *lf1;
    LinearForm<T> *lf2;
public:
    LinearFormUI();

    LinearForm<T> *CreationUI(int num);

    int OperationSelector();

    void MultiplyUI();

    void SumUI();

    void SubtructUI();

    void EvalUI();
};

template<class T>
LinearFormUI<T>::LinearFormUI() {
    lf1 = CreationUI(1);
    lf2 = CreationUI(2);

    while (true) {
        this->operation = OperationSelector();
        switch (this->operation) {
            case 1:
                MultiplyUI();
                break;
            case 2:
                SumUI();
                break;
            case 3:
                SubtructUI();
                break;
            case 4:
                EvalUI();
                break;
            case 5:
                return;
        }
    }
}

template<class T>
LinearForm<T> *LinearFormUI<T>::CreationUI(int num) {
    int size;
    T *items;

    cout << "Creation of linear form N" << num << endl;

    while (cout << "Enter size [>=1]:\n" && !((cin >> size) && (size >= 1))) {
        cin.clear();
        cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input; please re-enter.\n";
    }


    items = new T[size];

    cout << "Enter array:\n";
    for (int i = 0; i < size; ++i) {
        while (!(cin >> items[i])) {
            cin.clear();
            cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input; please re-enter (from wrong symbol).\n";
        }

    }

    LinearForm<T> *lf = new LinearForm<T>(items, size);

    return lf;
}

template<class T>
int LinearFormUI<T>::OperationSelector() {
    int choice;

    cout << "Linear form N1:" << endl;
    cout << *lf1 << endl;
    cout << "Linear form N2:" << endl;
    cout << *lf2 << endl;

    cout << "What do you want to do with these linear forms?" << endl
         << "1. Multiply one of them" << endl
         << "2. Sum them" << endl
         << "3. Substract them" << endl
         << "4. Eval one of them" << endl
         << "5. Exit" << endl;

    while (cout << "Enter a number [1-5]:\n" && !(cin >> choice) && !(choice >= 1 && choice <= 5)) {
        cin.clear();
        cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input; please re-enter.\n";
    }

    return choice;
}

template<class T>
void LinearFormUI<T>::MultiplyUI() {
    int source;
    T mult;

    cout << "Which you would like to multiply?" << endl;
    while (cout << "Enter a number [1-2]:\n" && !(cin >> source) && !(source >= 1 && source <= 2)) {
        cin.clear();
        cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input; please re-enter.\n";
    }

    while (cout << "Enter multiplier:\n" && !(cin >> mult)) {
        cin.clear();
        cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input; please re-enter.\n";
    }

    switch (source) {
        case 1:
            *(this->lf1) *= mult;
            break;
        case 2:
            *(this->lf2) *= mult;
            break;
    }
}

template<class T>
void LinearFormUI<T>::SumUI() {
    int destination;

    cout << "In which of linear forms do you want to save the answer?" << endl;
    while (cout << "Enter a number [1-2]:\n" && !(cin >> destination) && !(destination >= 1 && destination <= 2)) {
        cin.clear();
        cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input; please re-enter.\n";
    }

    switch (destination) {
        case 1:
            *(this->lf1) += *(this->lf2);
            break;
        case 2:
            *(this->lf2) += *(this->lf1);
            break;
    }

}

template<class T>
void LinearFormUI<T>::SubtructUI() {
    int destination;

    cout << "In which of linear forms do you want to save the answer?" << endl;
    while (cout << "Enter a number [1-2]:\n" && !(cin >> destination) && !(destination >= 1 && destination <= 2)) {
        cin.clear();
        cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input; please re-enter.\n";
    }

    switch (destination) {
        case 1:
            *(this->lf1) -= *(this->lf2);
            break;
        case 2:
            *(this->lf2) -= *(this->lf1);
            break;
    }
}

template<class T>
void LinearFormUI<T>::EvalUI() {
    int source;
    T *values;
    int size;

    cout << "Which of linear forms do you want to eval?" << endl;
    while (cout << "Enter a number [1-2]:\n" && !(cin >> source) && !(source >= 1 && source <= 2)) {
        cin.clear();
        cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input; please re-enter.\n";
    }

    switch (source) {
        case 1:
            size = this->lf1->GetLength() - 1;
            break;
        case 2:
            size = this->lf2->GetLength() - 1;
            break;
    }

    values = new T[size];

    cout << "Enter array of values (" << size << " argument(s)):\n";
    for (int i = 0; i < size; ++i) {
        while (!(cin >> values[i])) {
            cin.clear();
            cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input; please re-enter (from wrong symbol).\n";
        }

    }

    switch (source) {
        case 1:
            cout << "Result = " << this->lf1->eval(values, size) << endl;
            break;
        case 2:
            cout << "Result = " << this->lf2->eval(values, size) << endl;
            break;
    }
}
