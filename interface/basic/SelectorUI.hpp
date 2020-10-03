#pragma once

#include <iostream>
#include <string>

using namespace std;

class SelectorUI {
public:
    int choice;

    SelectorUI(string question, int count, string *answers);
};

SelectorUI::SelectorUI(string question, int count, string *answers) {
    cout << endl;

    cout << question << ":" << endl;

    for (int i = 0; i < count; ++i) {
        cout << i + 1 << ". " << answers[i] << endl;
    }


    while (cout << "Enter number [1-" << count << "]:\n" && !((cin >> this->choice) && (this->choice >= 1 && this->choice <= count))) {
        cin.clear();
        cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input; please re-enter.\n";
    }
}
