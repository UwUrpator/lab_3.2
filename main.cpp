#include <iostream>
#include "interface/UIStarter.hpp"

#include "source/Sorter/QuickSorter.hpp"

using namespace std;

int comparator(int a, int b) {
    if (a > b) {
        return 1;
    }
    if (a < b) {
        return -1;
    }

    return 0;
}

int main() {
    //UIStarter();
    int n = 3;

    int arr[] = {4, 2, 1};

    Sequence<int>* seq = new ArraySequence<int>(arr, 3);

    ShellSorter<int>* sorter = new ShellSorter<int>();

    Sequence<int>* seqSorted = sorter->Sort(seq, [](int a, int b) -> int { return a - b; });

    cout << seqSorted->Get(0) << " " << seqSorted->Get(1) << " " << seqSorted->Get(2) << endl;

    return 0;
}
