#pragma once

#include <iostream>
#include <string>

#include "../source/Sequence/Sequence.hpp"
#include "../source/ArraySequence/ArraySequence.hpp"
#include "../source/ListSequence/ListSequence.hpp"
#include "../source/Sorter/QuickSorter.hpp"
#include "../source/Sorter/ShellSorter.hpp"
#include "basic/SelectorUI.hpp"

class SortRandomDataUI {
private:
    int sort_choice;
    int seq_choice;
public:
    SortRandomDataUI();

    int SeqSelector();

    void SortArrSeq();
    void SortListSeq();
};

SortRandomDataUI::SortRandomDataUI() {
    while(true) {
        this->seq_choice = this->SeqSelector();

        switch(this->seq_choice) {
            case 1:
                this->SortArrSeq();
                break;
            case 2:
                this->SortListSeq();
                break;
            case 3:
                return;
        }
    }

}

int SortRandomDataUI::SeqSelector() {
    string answers[3] = {"Array", "List", "Exit"};
    return SelectorUI("What type of sequence do you want to use", 3, answers).choice;
}

void SortRandomDataUI::SortArrSeq() {

}

void SortRandomDataUI::SortListSeq() {

}

