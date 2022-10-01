/*
/ File name: red_black_tree.h
/ Project number: CSCE 221 Lab 5, Spring 2022
/ Date file was created: March 23, 2022
/ Section: 511
/ email address: vuthuynhi@tamu.edu
/ This header file is the implementation of the functions in class RedBlackTree, creates the tree, rotate the tree left and right, insert a node into the tree, remove a node from the tree,
/ fix the insertion and deletion by rotating the nodes and swapping its color, the insertion is going from top to bottom,
/ and display the results in the format specified in the project description.
*/

#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <cstddef>
#include <utility>
#include <iostream>

template <typename Comparable>
class RedBlackTree
{

private:
	struct Node
	{
		Comparable value;
		Node *left;
		Node *right;
		Node *parent;
		int color;

		Node(const Comparable &data)
		{
			value = data;
			left = nullptr;
			right = nullptr;
			parent = nullptr;
			color = BLACK;
		}

		Node(const Comparable &data, Node *left_child, Node *right_child, Node *parent_node, int colour = BLACK)
		{
			value = data;
			left = left_child;
			right = right_child;
			parent = parent_node;
			color = colour;
		}
	};

	Node *root;

	// name: copy
	// precondition: the tree doesn't have a copied version of it
	// postcondition: copies a version of the tree
	Node *copy(Node *node) const
	{
		if (node == nullptr)
		{
			return nullptr;
		}

		else
		{
			return new Node(node->value, copy(node->left), copy(node->right), node->parent, node->color);
		}
	}

	// name : display
	// precondition: the tree is not pretty displayed out to the console
	// postcondition: the tree is pretty displayed out to the console
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
			char c = node->color ? 'B' : 'R';
			out << c << ':' << node->value << "\n";
			display(node->left, out, counter + 1);
		}
	}

	// name: left_rotate
	// precondition: the node in the tree is not rotated left and the tree is unbalanced
	// postcondition: the node in the tree is rotated left and the tree is balanced
	void left_rotate(Node *node)
	{
		Node *temp = node->right;
		node->right = temp->left;
		if (temp->left != nullptr)
		{
			temp->left->parent = node;
		}

		temp->parent = node->parent;
		if (node->parent == nullptr)
		{
			this->root = temp;
		}
		else if (node == node->parent->left)
		{
			node->parent->left = temp;
		}
		else
		{
			node->parent->right = temp;
		}
		temp->left = node;
		node->parent = temp;
	}

	// name: right_rotate
	// precondition: the node in the tree is not rotated right and the tree is not balanced
	// postcondition: the node in the tree is rotated right and the tree is balanced
	void right_rotate(Node *node)
	{
		Node *temp = node->left;
		node->left = temp->right;

		if (temp->right != nullptr)
		{
			temp->right->parent = node;
		}

		temp->parent = node->parent;
		if (node->parent == nullptr)
		{
			this->root = temp;
		}
		else if (node == node->parent->right)
		{
			node->parent->right = temp;
		}
		else
		{
			node->parent->left = temp;
		}
		temp->right = node;
		node->parent = temp;
	}

	// name: handleReorient
	// precondition: top bottom insertion and the node in the tree has not been color swapped
	// postcondition: the black node with two red children has been color swapped and the tree has been rebalanced after inserting
	void handleReorient(Node *node)
	{

		Node *u;
		while (node->parent->color == RED)
		{
			if (node->parent == node->parent->parent->right)
			{
				u = node->parent->parent->left; // uncle
				if (u->color == RED)
				{
					// case 3.1
					u->color = BLACK;
					node->parent->color = BLACK;
					node->parent->parent->color = RED;
					node = node->parent->parent;
				}
				else
				{
					if (node == node->parent->left)
					{
						// case 3.2.2
						node = node->parent;
						right_rotate(node);
					}
					// case 3.2.1
					node->parent->color = BLACK;
					node->parent->parent->color = RED;
					left_rotate(node->parent->parent);
				}
			}
			else if (node->parent == node->parent->parent->left)
			{
				u = node->parent->parent->right; // uncle

				if (u->color == RED)
				{
					// mirror case 3.1
					u->color = BLACK;
					node->parent->color = BLACK;
					node->parent->parent->color = RED;
					node = node->parent->parent;
				}
				else
				{
					if (node == node->parent->right)
					{
						// mirror case 3.2.2
						node = node->parent;
						left_rotate(node);
					}
					// mirror case 3.2.1
					node->parent->color = BLACK;
					node->parent->parent->color = RED;
					right_rotate(node->parent->parent);
				}
			}
			if (node == root)
			{
				break;
			}
		}
		root->color = BLACK;
	}

	// name: right_subtree_min
	// precondition: the smallest node in the right subtree is unknown
	// postcondition: returns the smallest node in the right subtree

	Node *right_subtree_min(Node *node)
	{
		while (node->left != nullptr)
		{
			node = node->left;
		}

		return node;
	}

	// name: transplant
	// precondition: the two given nodes are not being replaced
	// postcondition: the two given nodes are being replaced
	void transplant(Node *node, Node *another_node)
	{
		if (node->parent == nullptr)
		{
			root = another_node;
		}
		else if (node == node->parent->left)
		{
			node->parent->left = another_node;
		}
		else
		{
			node->parent->right = another_node;
		}
		another_node->parent = node->parent;
	}

	// name: delete_fix
	// precondition: after the node is deleted from the tree, the tree is unbalanced and the rules are not being followed
	// postcondition: the tree is balanced and the rules are followed
	void delete_fix(Node *node)
	{
		Node *temp;
		while (node != root && node->color == BLACK)
		{
			if (node == node->parent->left)
			{
				temp = node->parent->right;
				if (temp->color == RED)
				{
					// case 3.1
					temp->color = BLACK;
					node->parent->color = RED;
					left_rotate(node->parent);
					temp = node->parent->right;
				}

				if (temp->left->color == BLACK && temp->right->color == BLACK)
				{
					// case 3.2
					temp->color = RED;
					node = node->parent;
				}
				else
				{
					if (temp->right->color == BLACK)
					{
						// case 3.3
						temp->left->color = BLACK;
						temp->color = RED;
						right_rotate(temp);
						temp = node->parent->right;
					}

					// case 3.4
					temp->color = node->parent->color;
					node->parent->color = BLACK;
					temp->right->color = BLACK;
					left_rotate(node->parent);
					node = root;
				}
			}
			else
			{
				temp = node->parent->left;
				if (temp->color == RED)
				{
					// case 3.1
					temp->color = BLACK;
					node->parent->color = RED;
					right_rotate(node->parent);
					temp = node->parent->left;
				}

				if (temp->right->color == BLACK && temp->right->color == BLACK)
				{
					// case 3.2
					temp->color = RED;
					node = node->parent;
				}
				else
				{
					if (temp->left->color == BLACK)
					{
						// case 3.3
						temp->right->color = BLACK;
						temp->color = RED;
						left_rotate(temp);
						temp = node->parent->left;
					}

					// case 3.4
					temp->color = node->parent->color;
					node->parent->color = BLACK;
					temp->left->color = BLACK;
					right_rotate(node->parent);
					node = root;
				}
			}
		}
		node->color = BLACK;
	}

	// name: delete_helper
	// precondition: the given value has not been found in the tree and couldn't be deleted
	// postcondition: the node containing the given value has been found in the tree
	void delete_helper(Node *node, const Comparable &data)
	{
		// find the node containing key
		Node *z = nullptr;
		Node *x, *y;
		while (node != nullptr)
		{
			if (node->value == data)
			{
				z = node;
			}

			if (node->value < data)
			{
				node = node->right;
			}
			else
			{
				node = node->left;
			}
		}

		y = z;
		int y_original_color = y->color;
		if (z->left == nullptr)
		{
			x = z->right;
			transplant(z, z->right);
		}
		else if (z->right == nullptr)
		{
			x = z->left;
			transplant(z, z->left);
		}
		else
		{
			y = right_subtree_min(z->right);
			y_original_color = y->color;
			x = y->right;
			if (y->parent == z)
			{
				x->parent = y;
			}
			else
			{
				transplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}

			transplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}
		delete z;
		if (y_original_color == BLACK)
		{
			delete_fix(x);
		}
	}

public:
	enum Color
	{
		RED,
		BLACK
	};
	RedBlackTree();
	RedBlackTree(const RedBlackTree &other);
	~RedBlackTree();
	RedBlackTree &operator=(const RedBlackTree &other);
	bool contains(const Comparable &data) const;
	void insert(const Comparable &data);
	void remove(const Comparable &data);
	const Comparable &find_min() const;
	const Comparable &find_max() const;
	void print_tree(std::ostream &os = std::cout) const;
	bool is_empty() const;
	void make_empty(Node *&node);
	void make_empty();

	// FOR TESTING ONLY - do not use these in your implementation
	int color(const Node *node) const
	{
		if (node == nullptr)
		{
			return BLACK;
		}
		else
		{
			return node->color;
		}
	}
	const Node *get_root() const
	{
		return root;
	}

	// Optional
	// RedBlackTree(RedBlackTree&& other);
	// RedBlackTree& operator=(RedBlackTree&& other);
	// void insert(Comparable&& value);
};

// name: constructor
// precondition: the red black tree is not created by this constructor
// postcondition: the red black tree is created
template <typename Comparable>
RedBlackTree<Comparable>::RedBlackTree()
{
	root = nullptr;
}

// name : copy constructor
// precondition: the red black tree does not have a copied version of it
// postcondition: the red black tree have a copied version of it
template <typename Comparable>
RedBlackTree<Comparable>::RedBlackTree(const RedBlackTree &other)
{
	root = nullptr;
	root = copy(other.root);
}

// name: destructor
// precondition: the red black tree has not been destroyed
// postcondition: the red black tree has been destroyed
template <typename Comparable>
RedBlackTree<Comparable>::~RedBlackTree()
{
	make_empty();
}

// name: copy assignment
// precondition: the red black tree has not been copied
// postcondition: the red black tree has been copied
template <typename Comparable>
RedBlackTree<Comparable> &RedBlackTree<Comparable>::operator=(const RedBlackTree &other)
{
	// self copied
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
// postcondition: returns true if the tree contains the given value and false otherwise
template <typename Comparable>
bool RedBlackTree<Comparable>::contains(const Comparable &data) const
{
	Node *node = root;
	while (node != nullptr)
	{
		if (node->value == data)
		{
			return true;
		}
		else if (node->value < data)
		{
			node = node->right;
		}
		else
		{
			node = node->left;
		}
	}
	return false;
}

// name: insert
// precondition: the given value has not been inserted into the tree
// postcondition: the given value has been inserted into the tree
template <typename Comparable>
void RedBlackTree<Comparable>::insert(const Comparable &data)
{
	// do nothing if the value is already in the tree
	if (contains(data))
	{
		;
	}
	else
	{
		Node *node = new Node(data);
		if (root == nullptr)
		{
			root = node;
		}
		else
		{
			Node *temp = root;
			Node *running_parent = nullptr;
			// the default node color is black but newly inserted nodes are red so we must update here
			node->color = RED;
			while (temp != nullptr)
			{
				running_parent = temp;
				if (data < temp->value)
				{
					temp = temp->left;
				}

				else if (data > temp->value)
				{
					temp = temp->right;
				}
			}

			node->parent = running_parent;
			if (running_parent == nullptr)
			{
				root = node;
			}
			else if (data > running_parent->value)
			{
				running_parent->right = node;
			}
			else
			{
				running_parent->left = node;
			}

			// if new node is root node, then returns
			if (node->parent == nullptr)
			{
				node->color = BLACK;
				;
			}
			if (node->parent->parent == nullptr)
			{
				;
			}
			handleReorient(node);
		}
	}
}

// name: remove
// precondition: the given value has not been removed from the tree
// postcondition: the given value has been removed from the tree
template <typename Comparable>
void RedBlackTree<Comparable>::remove(const Comparable &data)
{
	delete_helper(root, data);
}

// name: find_min
// precondition: the minimum value has not been found
// postcondition: returns the minimum value in the red black tree
template <typename Comparable>
const Comparable &RedBlackTree<Comparable>::find_min() const
{
	if (root == nullptr)
	{
		throw std::invalid_argument("tree is empty");
	}

	Node *node = root;
	while (node->left != nullptr)
	{
		node = node->left;
	}
	return node->value;
}

// name: find_max
// precondition: the maximum value has not been found
// postcondition: returns the maximum value in the red black tree
template <typename Comparable>
const Comparable &RedBlackTree<Comparable>::find_max() const
{
	if (root == nullptr)
	{
		throw std::invalid_argument("tree is empty");
	}
	Node *node = root;
	while (node->right != nullptr)
	{
		node = node->right;
	}

	return node->value;
}

// name: print_tree
// precondition: the tree has not been printed out to the console
// postcondition: the tree has been printed out to the console
template <typename Comparable>
void RedBlackTree<Comparable>::print_tree(std::ostream &out) const
{
	Node *node = root;
	display(node, out);
}

// name: is_empty
// precondition: do not know if the tree is empty or not
// postcondition: returns true if the tree is empty and false otherwise
template <typename Comparable>
bool RedBlackTree<Comparable>::is_empty() const
{
	if (root == nullptr)
	{
		return true;
	}
	return false;
}

// name: make_empty
// precondition: the red black tree is not empty
// postcondition: the red black tree is empty
template <typename Comparable>
void RedBlackTree<Comparable>::make_empty(Node *&node)
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
// precondition: the red black tree is not empty
// postcondition: remove all values from the tree until it is empty
template <typename Comparable>
void RedBlackTree<Comparable>::make_empty()
{
	make_empty(root);
}

#endif // RED_BLACK_TREE_H
