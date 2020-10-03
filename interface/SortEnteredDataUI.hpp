#pragma once

#include <iostream>
#include <string>
#include <chrono>

#include "../source/Sequence/Sequence.hpp"
#include "../source/ArraySequence/ArraySequence.hpp"
#include "../source/ListSequence/ListSequence.hpp"
#include "../source/Sorter/QuickSorter.hpp"
#include "../source/Sorter/ShellSorter.hpp"
#include "basic/SelectorUI.hpp"
#include "basic/SingleField.hpp"
#include "basic/MultiField.hpp"

class SortEnteredDataUI {
private:
    int length;

    int seq_choice;

    Sequence<int>* sequence;

    Sequence<int>* enterArrSeq(int length);
    Sequence<int>* enterListSeq(int length);

    int SeqSelector();
    int SeqMenu();

    void ArrSeqMenu();
    void ListSeqMenu();

    void SortSeq();

    void printSeq(Sequence<int>* seq);

public:
    SortEnteredDataUI();

};

SortEnteredDataUI::SortEnteredDataUI() {
    cout << endl;

    this->length = SingleField<int>("Enter length of sequence").item;

    while(true) {
        this->seq_choice = this->SeqSelector();

        switch(this->seq_choice) {
            case 1:
                this->ArrSeqMenu();
                break;
            case 2:
                this->ListSeqMenu();
                break;
            case 3:
                return;
        }
    }

}

int SortEnteredDataUI::SeqSelector() {
    string answers[3] = {"Array", "List", "Exit"};
    return SelectorUI("What type of sequence do you want to use", 3, answers).choice;
}

int SortEnteredDataUI::SeqMenu() {
    string answers[3] = {"Show source sequence", "Sort sequence", "Exit"};
    return SelectorUI("What do you want to do with enterd sequence", 3, answers).choice;
}

void SortEnteredDataUI::ArrSeqMenu() {
    this->sequence = this->enterArrSeq(this->length);

    while(true) {
        int menu_choice = this->SeqMenu();

        switch(menu_choice) {
            case 1:
                this->printSeq(this->sequence);
                break;
            case 2:
                this->SortSeq();
                break;
            case 3:
                return;
        }
    }
}

void SortEnteredDataUI::ListSeqMenu() {
    this->sequence = this->enterListSeq(this->length);

    while(true) {
        int menu_choice = this->SeqMenu();

        switch(menu_choice) {
            case 1:
                this->printSeq(this->sequence);
                break;
            case 2:
                this->SortSeq();
                break;
            case 3:
                return;
        }
    }
}

Sequence<int> *SortEnteredDataUI::enterArrSeq(int length) {
    int* arr = MultiField<int>("Enter values", length).items;

    Sequence<int>* seq = new ArraySequence<int>(arr, length);

    return seq;
}

Sequence<int> *SortEnteredDataUI::enterListSeq(int length) {
    int* arr = MultiField<int>("Enter values", length).items;

    Sequence<int>* seq = new ListSequence<int>(arr, length);

    return seq;
}


void SortEnteredDataUI::SortSeq() {
    auto start = chrono::high_resolution_clock::now();
    Sequence<int>* sortedSeq = QuickSorter<int>().Sort(this->sequence->Copy(), [](int a, int b) -> int { return a - b;});
    auto end = chrono::high_resolution_clock::now();

    auto milliseconds = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    cout << endl;
    cout << "Array sequence was sorted with Quick Sort for " << milliseconds << " ms." << endl
         << "Do you want to see result of sorted sequence? [y/n]" << endl;

    char choice;
    cin >> choice;

    switch (choice) {
        case 'y':
            this->printSeq(sortedSeq);
            break;
        default:
            break;
    }

    start = chrono::high_resolution_clock::now();
    sortedSeq = ShellSorter<int>().Sort(this->sequence->Copy(), [](int a, int b) -> int { return a - b;});
    end = chrono::high_resolution_clock::now();

    milliseconds = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    cout << endl;
    cout << "Array sequence was sorted with Shell Sort for " << milliseconds << " ms." << endl
         << "Do you want to see result of sorted sequence? [y/n]" << endl;

    choice;
    cin >> choice;

    switch (choice) {
        case 'y':
            this->printSeq(sortedSeq);
            break;
        default:
            break;
    }
}

void SortEnteredDataUI::printSeq(Sequence<int>* seq) {
    cout << "[ ";
    int length = seq->GetLength();

    for (int i = 0; i < length - 1; i++) {
        int current = seq->Get(i);

        cout << current << ", ";
    }

    cout << seq->Get(length - 1) << " ]" << endl;
}
