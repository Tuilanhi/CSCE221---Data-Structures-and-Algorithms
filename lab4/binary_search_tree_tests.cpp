/*
/ File name: binary_search_tree_tests.cpp
/ Project number: CSCE 221 Lab 4, Spring 2022
/ Date file was created: March 13, 2022
/ Section: 511
/ email address: vuthuynhi@tamu.edu
/ This cpp file contains the test files for the binary_search_tree.h header files, initializing the binary_search_tree, filling the values into the trees by iteration, checking to see if the tree is emtpy,
/ check to see if the tree contains a value, finding the maximum and minimum value in the tree, inserting and removing a given value in the tree, printing out the tree to the console, and finally make the tree empty.
*/

#include <iostream>
#include "binary_search_tree.h"

using std::cout;
using std::endl;

int main()
{
    // TODO(student): write tests
    // initializing and declaring a list with values
    int A[] = {4, 6, 5, 2, 1, 3};
    BinarySearchTree<int> tree;

    // is_empty
    // check to see if the tree is empty
    std::cout << "Is the tree empty? " << std::boolalpha << tree.is_empty() << std::endl;

    // filling the tree with values from list A using iteration
    for (size_t index = 0; index < 6; index++)
    {
        tree.insert(A[index]);
    }

    // print_tree
    //  print the tree
    tree.print_tree();

    // is_empty
    // check to see if the tree is empty
    std::cout << "Is the tree empty? " << std::boolalpha << tree.is_empty() << std::endl;

    // find_min
    // find the minimum element
    std::cout << "min: " << tree.find_min() << std::endl;

    // find_max
    // find the maximum element
    std::cout << "max: " << tree.find_max() << std::endl;

    // contains
    // search the tree
    std::cout << "contains 4? " << std::boolalpha << tree.contains(4) << std::endl;
    std::cout << "contains 7? " << std::boolalpha << tree.contains(7) << std::endl;

    // remove
    // remove the values
    tree.remove(6);

    // find_min
    // find the minimum element
    std::cout << "min: " << tree.find_min() << std::endl;

    // find_max
    // find the maximum element
    std::cout << "max: " << tree.find_max() << std::endl;

    // is_empty
    // check to see if the tree is empty
    std::cout << "Is the tree empty? " << std::boolalpha << tree.is_empty() << std::endl;

    // print_tree
    // print the tree
    std::cout << "tree: " << std::endl;
    tree.print_tree();

    // make_empty
    // make the tree empty
    tree.make_empty();

    // is_empty
    // check to see if the tree is empty
    std::cout << "Is the tree empty? " << std::boolalpha << tree.is_empty() << std::endl;

    // print_tree
    // print the tree
    std::cout << "tree: " << std::endl;
    tree.print_tree();

    return 0;
}
