#include <iostream>
#include "red_black_tree.h"

using std::cout, std::endl, std::cin;

int main() {
    // build a tree of ints
    RedBlackTree<int> rbt;
    cout << "enter whitespace-separated values, end with 0 or any non-integer value." << endl;
    cout << "positive integer value := insert(|value|)" << endl;
    cout << "negative integer value := remove(|value|)" << endl;
    cout << "-----" << endl;
    rbt.print_tree();
    cout << "-----" << endl;
    while(1) {
        int value = 0;
        cin >> value;
        if (cin.fail() || value == 0) { break; }
        cout << "-----" << endl;

        if (value > 0) {
            rbt.insert(value);
        } else {
            rbt.remove(-value);
        }

        rbt.print_tree();
        cout << "-----" << endl;
    }
}
