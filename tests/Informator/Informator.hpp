#pragma once

#include <iostream>

using namespace std;

class Informator {
public:
    Informator(bool expression, string t_message, string f_message);
};

Informator::Informator(bool expression, string t_message, string f_message) {
    if (expression) {
        cout << t_message << endl;
        return;
    }

    cout << f_message << endl;
}
