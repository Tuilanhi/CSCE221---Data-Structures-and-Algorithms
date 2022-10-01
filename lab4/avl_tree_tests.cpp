/*
/ File name: avl_tree_tests.cpp
/ Project number: CSCE 221 Lab 4, Spring 2022
/ Date file was created: March 13, 2022
/ Section: 511
/ email address: vuthuynhi@tamu.edu
/ The cpp file contains the test functions for AVLTree by initializing the tree, inserting the values into the tree, given values are removed, checked if the tree is empty
/ checked if the value is contained in the tree, remove the given value in the tree, finding the minimum and maximum values in the tree, and finally make the tree empty by
/ removing all the values.
*/

#include <iostream>
#include "avl_tree.h"

using std::cout;
using std::endl;

int main()
{
    // TODO(student): write tests

    // initializing and declaring a list with values

    AVLTree<int> tree;
    tree.insert(6);
    tree.insert(4);
    tree.insert(2);

    tree.print_tree();

    return 0;
}
