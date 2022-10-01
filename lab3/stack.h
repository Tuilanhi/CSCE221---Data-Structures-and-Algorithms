#ifndef STACK_H
#define STACK_H

#include <cstddef>
#include <stdexcept>
#include <iostream>
#include "doubly_linked_list.h"

template <typename Object>
class Stack
{
private:
	// TODO(student): implement Stack
	DoublyLinkedList<Object> list;

public:
	Stack();
	Stack(const Stack &other);
	~Stack();
	Stack &operator=(const Stack &other);
	void push(const Object &item);
	Object pop();
	Object &top();
	size_t size() const;
};

// initialize stack
template <typename Object>
Stack<Object>::Stack() : list(){};

// create a copy stack
template <typename Object>
Stack<Object>::Stack(const Stack &other)
{
	list = other.list;
}

// delete the stack
template <typename Object>
Stack<Object>::~Stack()
{
	list.clear_list();
}

// copy the stack into a otherStack
template <typename Object>
Stack<Object> &Stack<Object>::operator=(const Stack &other)
{
	if (&other == this)
	{
		return *this;
	}

	list = other.list;
	return *this;
}
// insert the given object into the stack by pushing it on top
template <typename Object>
void Stack<Object>::push(const Object &item)
{
	// push the item on top of the stack
	list.insertAtBack(item);
}

// remove the next value in the stack and return the item value
template <typename Object>
Object Stack<Object>::pop()
{
	if (list.size() == 0)
	{
		throw std::out_of_range("Cannot remove from an empty list");
	}
	Object index = list[list.size() - 1];
	// remove the top most item in the stack
	list.remove(list.size() - 1);
	// return the value of that item
	return index;
}
// return a reference to the next item in the stack
template <typename Object>
Object &Stack<Object>::top()
{
	if (list.size() == 0)
	{
		throw std::out_of_range("Cannot return an empty stack");
	}

	return list[list.size() - 1];
}

// return the number of elements in the stack
template <typename Object>
size_t Stack<Object>::size() const
{
	return list.size();
}

#endif // STACK_H
