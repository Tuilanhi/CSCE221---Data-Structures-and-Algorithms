/*
/ File name: red_black_tree_tests.cpp
/ Project number: CSCE 221 Lab 5, Spring 2022
/ Date file was created: March 23, 2022
/ Section: 511
/ email address: vuthuynhi@tamu.edu
/ This cpp file contains the test files for the red_black_tree_tests.h header files, initializing the red black tree, filling the values into the trees by iteration, checking to see if the tree is emtpy,
/ check to see if the tree contains a value, finding the maximum and minimum value in the tree, inserting and removing a given value in the tree, printing out the tree to the console, and finally make the tree empty.
*/

#include <iostream>
#include <sstream>
#include "red_black_tree.h"

using std::cout, std::endl;

int main()
{
    // make an empty tree
    RedBlackTree<int> tree;

    // name: insert
    // insert 5 values into the tree
    std::cout << "insert 6, 4, 8, 10, 2, 7, 23 " << std::endl;
    tree.insert(6);
    tree.insert(4);
    tree.insert(8);
    tree.insert(10);
    tree.insert(2);
    tree.insert(7);
    tree.insert(23);

    // name: is_empty
    // checks if the tree is empty
    cout << "is the tree empty? " << std::boolalpha << tree.is_empty() << std::endl;

    // name: print_tree
    // print the tree
    std::cout << "tree: " << std::endl;
    {
        std::ostringstream ss;
        tree.print_tree(ss);
        std::cout << ss.str() << std::endl;
    }

    // name: contains
    // checks if the tree contains the value
    std::cout << "contains 4? " << std::boolalpha << tree.contains(4) << std::endl;
    std::cout << "contains 7? " << std::boolalpha << tree.contains(7) << std::endl;

    // name: remove
    // remove the root
    std::cout << "remove 4" << std::endl;
    tree.remove(4);

    // name: find_min
    // find the minimum element
    std::cout << "min: " << tree.find_min() << std::endl;

    // name: find_max
    // find the maximum element
    std::cout << "max: " << tree.find_max() << std::endl;

    // name: is_empty
    // checks if the tree is empty
    cout << "is the tree empty? " << std::boolalpha << tree.is_empty() << std::endl;

    // name: print_tree
    // print the tree
    std::cout << "tree: " << std::endl;
    {
        std::ostringstream ss;
        tree.print_tree(ss);
        std::cout << ss.str() << std::endl;
    }

    // name: make_empty
    // delete all the nodes in the tree
    tree.make_empty();

    cout << "is the tree empty? " << std::boolalpha << tree.is_empty() << std::endl;

    // name: print_tree
    // print the tree
    std::cout << "tree: " << std::endl;
    {
        std::ostringstream ss;
        tree.print_tree(ss);
        std::cout << ss.str() << std::endl;
    }

    return 0;
}