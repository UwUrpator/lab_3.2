#pragma once

#include <iostream>
#include <string>

#include "../source/Sequence/Sequence.hpp"
#include "../source/ArraySequence/ArraySequence.hpp"
#include "../source/ListSequence/ListSequence.hpp"
#include "../source/Sorter/QuickSorter.hpp"
#include "../source/Sorter/ShellSorter.hpp"
#include "../interface/SelectorUI.hpp"

class SortRandomDataUI {
private:
    int sort_choice;
    int seq_choice;
public:
    SortRandomDataUI();

    int SortSelector();
    int SeqSelector();

    void QuickSortUI();
    void ShellSortUI();

    void QuickSortArrSeqUI();
    void QuickSortListSeqUI();
    void ShellSortArrSeqUI();
    void ShellSortListSeqUI();
};

SortRandomDataUI::SortRandomDataUI() {
    while(true) {
        this->sort_choice = this->SortSelector();

        switch(this->sort_choice) {
            case 1:
                this->QuickSortUI();
               break;
            case 2:
                this->ShellSortUI();
                break;
            case 3:
                return;
        }
    }
}

int SortRandomDataUI::SortSelector() {
    string answers[3] = {"Quick sort", "Shell sort", "Exit"};
    return SelectorUI( "What sort algorithm do you want to use", 3, answers).choice;
}

int SortRandomDataUI::SeqSelector() {
    string answers[3] = {"Array", "List", "Exit"};
    return SelectorUI("What type of sequence do you want to use", 3, answers).choice;
}

void SortRandomDataUI::QuickSortUI() {
    while(true) {
        this->seq_choice = this->SeqSelector();

        switch(this->seq_choice) {
            case 1:
                this->QuickSortArrSeqUI();
                break;
            case 2:
                this->QuickSortListSeqUI();
                break;
            case 3:
                return;
        }
    }
}

void SortRandomDataUI::ShellSortUI() {
    while(true) {
        this->seq_choice = this->SeqSelector();

        switch(this->seq_choice) {
            case 1:
                this->ShellSortArrSeqUI();
                break;
            case 2:
                this->ShellSortListSeqUI();
                break;
            case 3:
                return;
        }
    }
}

void SortRandomDataUI::QuickSortArrSeqUI() {

}

void SortRandomDataUI::QuickSortListSeqUI() {

}

void SortRandomDataUI::ShellSortArrSeqUI() {

}

void SortRandomDataUI::ShellSortListSeqUI() {

}
