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

class SortRandomDataUI {
private:
    int length;

    int seq_choice;

    Sequence<int>* sequence;

    Sequence<int>* generateArrSeq(int length);
    Sequence<int>* generateListSeq(int length);

    int SeqSelector();
    int SeqMenu();

    void ArrSeqMenu();
    void ListSeqMenu();

    void SortSeq();

    void printSeq(Sequence<int>* seq);

public:
    SortRandomDataUI();

};

SortRandomDataUI::SortRandomDataUI() {
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

int SortRandomDataUI::SeqSelector() {
    string answers[3] = {"Array", "List", "Exit"};
    return SelectorUI("What type of sequence do you want to use", 3, answers).choice;
}

int SortRandomDataUI::SeqMenu() {
    string answers[3] = {"Show source sequence", "Sort sequence", "Exit"};
    return SelectorUI("What do you want to do with generated sequence", 3, answers).choice;
}

void SortRandomDataUI::ArrSeqMenu() {
    this->sequence = this->generateArrSeq(this->length);

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

void SortRandomDataUI::ListSeqMenu() {
    this->sequence = this->generateListSeq(this->length);

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

Sequence<int> *SortRandomDataUI::generateArrSeq(int length) {
    Sequence<int>* seq = new ArraySequence<int>(length);

    for (int i = 0; i < length; ++i) {
        int random = rand() - RAND_MAX / 2;

        seq->Set(random, i);
    }

    return seq;
}

Sequence<int> *SortRandomDataUI::generateListSeq(int length) {
    int* arr = new int[length];

    for (int i = 0; i < length; ++i) {
        int random = rand() - RAND_MAX / 2;

        arr[i] = random;
    }

    Sequence<int>* seq = new ListSequence<int>(arr, length);

    return seq;
}


void SortRandomDataUI::SortSeq() {
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

void SortRandomDataUI::printSeq(Sequence<int>* seq) {
    cout << "[ ";
    int length = seq->GetLength();

    for (int i = 0; i < length - 1; i++) {
        int current = seq->Get(i);

        cout << current << ", ";
    }

    cout << seq->Get(length - 1) << " ]" << endl;
}
