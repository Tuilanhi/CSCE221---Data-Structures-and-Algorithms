/*
/ File name: avl_tree.h
/ Project number: CSCE 221 Lab 4, Spring 2022
/ Date file was created: March 13, 2022
/ Section: 511
/ email address: vuthuynhi@tamu.edu
/ This header file is the implementation of the functions in class AVLTree, creates the tree, balance the tree, rotate the tree left and right, insert a node into the tree, remove a node from the tree
/ and display the results in the format specified in the project description.
*/

#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <cstddef>
#include <iostream>

template <typename Comparable>
class AVLTree
{
    // TODO(student): implement AVLTree
private:
    struct Node
    {
        Comparable data;
        Node *left;
        Node *right;
        int height;

        // name: Node
        // precondition: struct Node has not been declared
        // postcondition: all the data has been declared
        Node(const Comparable &value)
        {
            data = value;
            left = nullptr;
            right = nullptr;
            height = 0;
        }

        // name: Node
        // precondition: struct Node has not been declared with the given value, left node, right node, and the height
        // postcondition: all the data has been declared
        Node(const Comparable &value, Node *_left, Node *_right, int _height = 0)
        {
            data = value;
            left = _left;
            right = _right;
            height = _height;
        }
    };

    Node *root;

    // Name: balance
    // Precondition: the tree is unbalanced
    // Postcondition: the tree is balanced
    void balance(Node *&node)
    {
        if (node == nullptr)
        {
            return;
        }
        if (height(node->left) - height(node->right) > 1)
        {
            if (height(node->left->left) >= height(node->left->right))
            {
                lc_rotate(node);
            }
            else
            {
                dlc_rotate(node);
            }
        }
        else if (height(node->right) - height(node->left) > 1)
        {
            if (height(node->right->right) >= height(node->right->left))
            {
                rc_rotate(node);
            }
            else
            {
                drc_rotate(node);
            }
        }

        node->height = std::max(height(node->left), height(node->right)) + 1;
    }

    // Name: copy
    // Precondition: the tree doesn't have a copied version of it
    // postcondition: copies a version of the tree
    Node *copy(Node *node) const
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        else
        {
            return new Node(node->data, copy(node->left), copy(node->right), node->height);
        }
    }

    // name: display
    // Precondition: the avl tree is not displayed to the console
    // Postcondition: the avl tree is displayed to the console
    void display(Node *node, std::ostream &out = std::cout, unsigned int counter = 0) const
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

    // name: dlc_rotate
    // precondition: the node is in the inner left sub tree
    // postcondition: the tree is rotated to the right and then to the left
    void dlc_rotate(Node *&node)
    {
        rc_rotate(node->left);
        lc_rotate(node);
    }

    // name: drc_rotate
    // precondition: the node is in the inner right sub tree
    // postcondition: the tree is rotated to the left and then to the right
    void drc_rotate(Node *&node)
    {
        lc_rotate(node->right);
        rc_rotate(node);
    }

    // name: insert
    // precondition: the tree does not have the value inserted
    // postcondition: the value is inserted into the tree
    void insert(const Comparable &value, Node *&node)
    {
        if (node == nullptr)
        {
            node = new Node(value, nullptr, nullptr);
        }
        else if (value < node->data)
        {
            insert(value, node->left);
        }
        else if (value > node->data)
        {
            insert(value, node->right);
        }

        balance(node);
    }

    // name: height
    // precondition: the tree's height
    // postcondition: returns the tree's height
    int height(Node *node) const
    {
        return node == nullptr ? -1 : node->height;
    }

    // name: lc_rotate
    // precondition: the tree needs to be rotated to the left
    // postcondition: the tree is rotated left
    void lc_rotate(Node *&node)
    {
        Node *left_child = node->left;
        node->left = left_child->right;
        left_child->right = node;
        node->height = std::max(height(node->left), height(node->right)) + 1;
        left_child->height = std::max(height(left_child->left), node->height) + 1;
        node = left_child;
    }

    // name : rc_rotate
    // precondition: the tree is not rotated to the right
    // postcondition: the tree is rotated to the right
    void rc_rotate(Node *&node)
    {
        Node *right_child = node->right;
        node->right = right_child->left;
        right_child->left = node;
        node->height = std::max(height(node->left), height(node->right)) + 1;
        right_child->height = std::max(height(right_child->right), node->height) + 1;
        node = right_child;
    }

    // name: right_subtree_min
    // precondition: the value of the node on the left of the right subtree
    // postcondition: returns the value of the node on the most left of the right subtree
    Comparable &right_subtree_min(Node *node) const
    {
        while (node->left != nullptr)
        {
            node = node->left;
        }

        return node->data;
    }

    // name: remove
    // precondition: the value in the tree is not removed
    // postcondition: the value in the tree is removed
    void remove(const Comparable &value, Node *&node)
    {
        if (node == nullptr)
        {
            return;
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
            node->data = right_subtree_min(node->right);
            remove(node->data, node->right);
        }
        else
        {
            Node *node_to_remove = node;
            node = node->left != nullptr ? node->left : node->right;
            delete node_to_remove;
        }

        balance(node);
    }

public:
    AVLTree();
    AVLTree(const AVLTree &other);
    ~AVLTree();
    AVLTree &operator=(const AVLTree &other);
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
    // AVLTree(AVLTree&& other);
    // AVLTree& operator=(AVLTree&& other);
    // void insert(Comparable&& value);
};

// name: constructor
// precondition: the avl tree is not created
// postcondition: the avl tree is created and initialized
template <typename Comparable>
AVLTree<Comparable>::AVLTree()
{
    root = nullptr;
}

// name : copy constructor
// precondition: the avl tree did not have a copied version of it
// postcondition: the avl tree constructed a copied version of it
template <typename Comparable>
AVLTree<Comparable>::AVLTree(const AVLTree &other)
{
    root = nullptr;
    root = copy(other.root);
}

// name: destructor
// precondition: the avl tree has not been destroyed
// postcondition: the avl tree has been destroyed
template <typename Comparable>
AVLTree<Comparable>::~AVLTree()
{
    make_empty();
}

// name: copy assignment operator
// precondition: the avl tree has not been copied
// postcondition: the avl tree has been copied to a copy constructor
template <typename Comparable>
AVLTree<Comparable> &AVLTree<Comparable>::operator=(const AVLTree &other)
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
// precondition: does not know if the avl tree contains the given value
// postcondition: returns true if the specified value is in the tree
template <typename Comparable>
bool AVLTree<Comparable>::contains(const Comparable &value) const
{
    Node *temp = root;
    while (temp != nullptr)
    {
        if (temp->data == value)
        {
            return true;
        }
        else if (temp->data < value)
        {
            temp = temp->right;
        }
        else
        {
            temp = temp->left;
        }
    }

    return false;
}

// name: insert
// precondition: the value is not inserted into the avl tree
// postcondition: the value is inserted into the AVLTree
template <typename Comparable>
void AVLTree<Comparable>::insert(const Comparable &value)
{
    if (contains(value))
    {
        ;
    }
    else
    {
        insert(value, root);
    }
}

// name: remove
// precondition: the value is not removed from the tree
// postcondition: remove the given value from the AVLTree
template <typename Comparable>
void AVLTree<Comparable>::remove(const Comparable &value)
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
// postcondition: return the minimum value in the AVLTree
template <typename Comparable>
const Comparable &AVLTree<Comparable>::find_min() const
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
// postcondition: return the maximum value in the AVLTree
template <typename Comparable>
const Comparable &AVLTree<Comparable>::find_max() const
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
void AVLTree<Comparable>::print_tree(std::ostream &os) const
{
    Node *temp = root;
    display(temp, os);
}

// name: is_empty
// precondition: do not know if the tree is empty or not
// postcondition: return true if the AVLTree is empty
template <typename Comparable>
bool AVLTree<Comparable>::is_empty() const
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
void AVLTree<Comparable>::make_empty(Node *&node)
{
    if (node != nullptr)
    {
        make_empty(node->left);
        make_empty(node->right);
        delete node;
    }

    node = nullptr;
}

// name: make_emptys
// precondition: the tree is not empty
// postcondition: all the values in the tree has been removed when calling the recursion function
template <typename Comparable>
void AVLTree<Comparable>::make_empty()
{
    make_empty(root);
}
#endif
