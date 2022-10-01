/*
/ File name: heap.h
/ Project number: CSCE 221 Lab 6, Spring 2022
/ Date file was created: April 13, 2022
/ Section: 511
/ email address: vuthuynhi@tamu.edu
/ This header file is the implementation of the functions in class Heap, the min heap is being implemented using the heapify function
/ which compares each value inserted into the function by comparing each value with its parent
/ the parent node should be smaller compared to its children, and the highest level does not have to be sorted.
*/

#ifndef HEAP_H
#define HEAP_H

#include <functional>
#include <vector>

// name: percolate_down
// precondition: the values have not been moved down the binary tree if it is larger than its children
// postcondition: the value has been percolate down the binary tree
template <class Container, class Compare = std::less<typename Container::value_type> >
void percolate_down(Container *container, size_t index, Compare less = std::less<typename Container::value_type>{})
{
    // TODO(student): implement percolate_down
    if (index <= 0 || index >= container->size() || container->size() <= 1)
    {
        throw std::invalid_argument(__FUNCTION__);
    }

    size_t child;
    typename Container::value_type value = container->at(index);
    while (index * 2 < container->size())
    {
        child = index * 2;
        if (child != container->size() - 1 && less(container->at(child + 1), container->at(child)))
        {
            child++;
        }
        if (less(container->at(child), value))
        {
            container->at(index) = std::move(container->at(child));
        }
        else
        {
            break;
        }
        index = child;
    }
    container->at(index) = std::move(value);
}

// name: heapify
// precondition: the binary tree has not been heapified
// postcondition: the binary tree has been heapified, and created a min heap tree
template <class Container, class Compare = std::less<typename Container::value_type> >
void heapify(Container *container, Compare less = std::less<typename Container::value_type>{})
{
    // TODO(student): implement heapify
    if (container->size() < 1)
    {
        return;
    }

    container->insert(container->begin(), typename Container::value_type{});

    for (size_t i = container->size() / 2; i > 0; i--)
    {
        percolate_down(container, i, less);
    }
}

// GIVEN: The functions below are given to you in the starter code
// you should NOT need to modify these

template <class Container, class Compare = std::less<typename Container::value_type> >
void heap_insert(Container *container, const typename Container::value_type &value, Compare less = std::less<typename Container::value_type>{})
{
    if (container->size() <= 1)
    {
        container->resize(2);
        container->at(1) = std::move(value);
        return;
    }
    size_t index = container->size();
    container->push_back(value);
    size_t parent = index / 2;
    while (parent > 0 && less(value, container->at(parent)))
    {
        container->at(index) = std::move(container->at(parent));
        index = parent;
        parent = index / 2;
    }
    container->at(index) = std::move(value);
}

template <class Container>
const typename Container::value_type &heap_get_min(const Container &container)
{
    if (container.size() <= 1)
    {
        throw std::invalid_argument(__FUNCTION__);
    }
    return container[1];
}

template <class Container, class Compare = std::less<typename Container::value_type> >
void heap_delete_min(Container *container, Compare less = std::less<typename Container::value_type>{})
{
    if (container->size() <= 1)
    {
        throw std::invalid_argument(__FUNCTION__);
    }
    if (container->size() == 2)
    {
        container->pop_back();
        return;
    }
    container->at(1) = std::move(container->back());
    container->pop_back();
    percolate_down(container, 1, less);
}

#endif // HEAP_H