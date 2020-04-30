#pragma once

#include "../tests/TestRunner.hpp"
#include "../source/LinearForm/LinearForm.hpp"
#include "LinearFormUI.hpp"

class UIStarter {
private:
    int type;

public:
    UIStarter();

    int typeSelector();

};

UIStarter::UIStarter() {
    TestRunner();

    cout << endl;

    this->type = typeSelector();
    switch (this->type) {
        case 1:
            LinearFormUI<int>();
            break;
        case 2:
            LinearFormUI<double>();
            break;
        case 3:
            LinearFormUI<complex<double>>();
            break;
    }
}

int UIStarter::typeSelector() {
    int choice;

    cout << "Which type of linear form do you want to work with?:" << endl
         << "1. Integer" << endl
         << "2. Double" << endl
         << "3. Complex" << endl;


    while (cout << "Enter number [1-3]:\n" && !((cin >> choice) && (choice >= 1 && choice <= 3))) {
        cin.clear();
        cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input; please re-enter.\n";
    }


    return choice;
}


