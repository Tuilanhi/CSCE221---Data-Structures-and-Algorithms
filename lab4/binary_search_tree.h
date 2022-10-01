/*
/ File name: binary_search_tree.h
/ Project number: CSCE 221 Lab 4, Spring 2022
/ Date file was created: March 13, 2022
/ Section: 511
/ email address: vuthuynhi@tamu.edu
/ This header file is the implementation of the functions in class AVLTree, creates the tree, balance the tree, rotate the tree left and right, insert a node into the tree, remove a node from the tree,
/ make the tree empty by removing all the nodes, and display the results in the format specified in the project description.
*/

#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <cstddef>
#include <iostream>

template <typename Comparable>
class BinarySearchTree
{
    // TODO(student): implement BinarySearchTree
private:
    struct Node
    {
        Comparable data;
        Node *left;
        Node *right;

        // name: Node
        // precondition: struct Node has not been declared
        // postcondition: all the data has been declared
        Node(const Comparable &value)
        {
            data = value;
            left = nullptr;
            right = nullptr;
        }

        // name: Node
        // precondition: struct Node has not been declared with the given value, left node, right node
        // postcondition: all the data has been declared
        Node(const Comparable &value, Node *_left, Node *_right)
        {
            data = value;
            left = _left;
            right = _right;
        }
    };

    Node *root;

    // Name: copy
    // Precondition: the binary search tree doesn't have a copied version of it
    // postcondition: copies a version of the tree
    Node *copy(Node *node) const
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        else
        {
            return new Node(node->data, copy(node->left), copy(node->right));
        }
    }

    // name: right_subtree_min
    // precondition: the value of the node on the left of the right subtree
    // postcondition: returns the value of the node on the most left of the right subtree
    Node *right_subtree_min(Node *node) const
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        if (node->left == nullptr)
        {
            return node;
        }
        return right_subtree_min(node->left);
    }

    // name: remove
    // precondition: the value in the tree is not removed
    // postcondition: the value in the tree is removed
    void remove(const Comparable &value, Node *&node)
    {
        if (node == nullptr)
        {
            ;
        }
        if (value < node->data)
        {
            remove(value, node->left);
        }
        else if (value > node->data)
        {
            remove(value, node->right);
        }
        else if (node->left != nullptr && node->right != nullptr)
        {
            node->data = right_subtree_min(node->right)->data;
            remove(node->data, node->right);
        }
        else
        {
            Node *node_to_remove = node;
            node = node->left != nullptr ? node->left : node->right;
            delete node_to_remove;
        }
    }

    // name: display
    // Precondition: the binary search tree is not displayed to the console
    // Postcondition: the binary search tree is displayed to the console
    void display(Node *node, std::ostream &out, unsigned int counter = 0) const
    {
        if (root == nullptr)
        {
            out << "<empty>\n";
        }
        else if (node == nullptr)
        {
            out << "";
        }
        else
        {
            display(node->right, out, counter + 1);
            for (unsigned int i = 0; i < counter; i++)
            {
                out << "  ";
            }
            out << node->data << "\n";
            display(node->left, out, counter + 1);
        }
    }

public:
    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree &other);
    ~BinarySearchTree();
    BinarySearchTree &operator=(const BinarySearchTree &other);
    bool contains(const Comparable &value) const;
    void insert(const Comparable &value);
    void remove(const Comparable &value);
    const Comparable &find_min() const;
    const Comparable &find_max() const;
    void print_tree(std::ostream &os = std::cout) const;
    bool is_empty() const;
    void make_empty();
    void make_empty(Node *&node);

    // optional
    // BinarySearchTree(BinarySearchTree&& other);
    // BinarySearchTree& operator=(BinarySearchTree&& other);
    // void insert(Comparable&& value);
};

// name: constructor
// precondition: the binary search tree is not created
// postcondition: the binary search tree is created and initialized
template <typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree()
{
    root = nullptr;
}

// name : copy constructor
// precondition: the binary search tree did not have a copied version of it
// postcondition: the binary search tree constructed a copied version of it
template <typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(const BinarySearchTree &other)
{
    root = copy(other.root);
}

// name: destructor
// precondition: the binary search tree has not been destroyed
// postcondition: the binary search tree has been destroyed
template <typename Comparable>
BinarySearchTree<Comparable>::~BinarySearchTree()
{
    make_empty();
}

// name: copy assignment operator
// precondition: the binary search tree has not been copied
// postcondition: the binary search tree has been copied to a copy constructor
template <typename Comparable>
BinarySearchTree<Comparable> &BinarySearchTree<Comparable>::operator=(const BinarySearchTree &other)
{
    if (&other == this)
    {
        return *this;
    }

    make_empty();
    root = copy(other.root);
    return *this;
}

// name: contains
// precondition: does not know if the tree contains the given value
// postcondition: returns true if the specified value is in the tree
template <typename Comparable>
bool BinarySearchTree<Comparable>::contains(const Comparable &value) const
{
    Node *new_node = root;
    while (new_node != nullptr)
    {
        if (new_node->data == value)
        {
            return true;
        }
        else if (new_node->data < value)
        {
            new_node = new_node->right;
        }
        else
        {
            new_node = new_node->left;
        }
    }

    return false;
}

// name: insert
// precondition: the value is not inserted into the binary search tree
// postcondition: the value is inserted into the tree
template <typename Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable &value)
{
    if (contains(value))
    {
        ;
    }
    else
    {
        Node *new_node = new Node(value);
        if (root == nullptr)
        {
            root = new_node;
        }
        else
        {
            Node *temp = root;
            while ((temp->left != nullptr && value < temp->data) || (temp->right != nullptr && value > temp->data))
            {
                if (value < temp->data)
                {
                    temp = temp->left;
                }
                else if (value > temp->data)
                {
                    temp = temp->right;
                }
            }

            if (value > temp->data)
            {
                temp->right = new_node;
            }
            else
            {
                temp->left = new_node;
            }
        }
    }
}

// name: remove
// precondition: the value is not removed from the tree
// postcondition: remove the given value from the binary search tree
template <typename Comparable>
void BinarySearchTree<Comparable>::remove(const Comparable &value)
{
    if (!contains(value))
    {
        ;
    }
    else
    {
        remove(value, root);
    }
}

// name: find_min
// precondition: the minimum value is has not been found
// postcondition: return the minimum value in the tree
template <typename Comparable>
const Comparable &BinarySearchTree<Comparable>::find_min() const
{
    if (is_empty())
    {
        throw std::invalid_argument("tree is empty");
    }

    Node *temp = root;
    while (temp->left != nullptr)
    {
        temp = temp->left;
    }

    return temp->data;
}

// name: find_max
// precondition: the maximum value is has not been found
// postcondition: return the maximum value in the tree
template <typename Comparable>
const Comparable &BinarySearchTree<Comparable>::find_max() const
{
    if (is_empty())
    {
        throw std::invalid_argument("tree is empty");
    }

    Node *temp = root;
    while (temp->right != nullptr)
    {
        temp = temp->right;
    }

    return temp->data;
}

// name: print_tree
// precondition: the tree has not been printed out to the console
// postcondition: pretty print the tree rorate 90 degree to the left, two spaces per level. Print "<empty>\n" if the tree is empty
template <typename Comparable>
void BinarySearchTree<Comparable>::print_tree(std::ostream &os) const
{
    Node *temp = root;
    display(temp, os);
}

// name: is_empty
// precondition: do not know if the tree is empty or not
// postcondition: return true if the binary search tree is empty
template <typename Comparable>
bool BinarySearchTree<Comparable>::is_empty() const
{
    if (root == nullptr)
    {
        return true;
    }
    return false;
}

// name: make_empty
// precondition: the tree is not empty
// postcondition: all the values in the tree has been removed using recursion
template <typename Comparable>
void BinarySearchTree<Comparable>::make_empty(Node *&node)
{
    if (node != nullptr)
    {
        make_empty(node->left);
        make_empty(node->right);
        delete node;
    }

    node = nullptr;
}

// name: make_empty
// precondition: the tree is not empty
// postcondition: all the values in the tree has been removed when calling the recursion function
template <typename Comparable>
void BinarySearchTree<Comparable>::make_empty()
{
    make_empty(root);
}
#endif
