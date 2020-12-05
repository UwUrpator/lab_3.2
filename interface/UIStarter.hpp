#pragma once

#include "../tests/TestRunner.hpp"
#include "EnterCacheUI.hpp"
#include "basic/SelectorUI.hpp"

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
                EnterCacheUI();
                break;
            case 3:
                return;
        }
    }
}

int UIStarter::Selector() {
    string answers[3] = {"Run tests", "Work with cache", "Exit"};
    return SelectorUI("What do you want to do", 3, answers).choice;
}
