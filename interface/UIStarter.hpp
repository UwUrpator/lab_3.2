#pragma once

#include "../tests/TestRunner.hpp"
#include "../source/LinearForm/LinearForm.hpp"
//#include "LinearFormUI.hpp"
#include "SortRandomDataUI.hpp"
#include "SortEnteredDataUI.hpp"

class UIStarter {
public:
    UIStarter();

    int Selector();
};

UIStarter::UIStarter() {
    while (true) {
        int choice = Selector();
        switch (choice) {
            case 1:
                TestRunner();
                break;
            case 2:
                SortRandomDataUI();
                break;
            case 3:
                //???
                break;
            case 4:
                return;
        }
    }
}

int UIStarter::Selector() {
    string answers[4] = {"Run tests", "Sort random data", "Sort entered data", "Exit"};
    return SelectorUI("What do you want to do", 4, answers).choice;
}
