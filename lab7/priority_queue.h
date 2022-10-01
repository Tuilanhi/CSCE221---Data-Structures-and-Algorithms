/*
/ File name: priority_queue.h
/ Project number: CSCE 221 Lab 7, Spring 2022
/ Date file was created: April 13, 2022
/ Section: 511
/ email address: vuthuynhi@tamu.edu
/ This header file is the implementation of the functions in class PriorityQueue, in which it creates the PriorityQueue using both container_type container and value_type compare, it also uses the header file heap.h to help
/ implement the functions and insert as well as deleting values from the PriorityQueue. We also check for whether the PriorityQueue is empty, returns the size, the minimum value, and if it it not empty,
/ remove all values from the queue, and lastly prints out the values pretty.
*/

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <iostream>
#include <vector>
#include <functional>
#include "heap.h"

template <class Comparable, class Container = std::vector<Comparable>, class Compare = std::less<Comparable> >
class PriorityQueue
{
private:
    // Member Types - do not modify
    using container_type = Container;
    using value_compare = Compare;
    using value_type = typename Container::value_type;
    using size_type = typename Container::size_type;
    using reference = typename Container::reference;
    using const_reference = typename Container::const_reference;
    // Member Types - do not modify
    // you can modify below here

    Compare compare;
    Container container;

public:
    // name: default constructor
    // precondition: the compare and container have not been created
    // postcondition: the compare and container have been created
    PriorityQueue() : PriorityQueue(Compare(), Container()) {}

    // name: parameterized constructor
    // precondition: the compare and container have not been created
    // postcondition: the compare and container have been created
    PriorityQueue(const PriorityQueue &other) : container(other.container), compare(other.compare) {}

    // name: parameterized constructor
    // precondition: the compare have not been copied to _compare
    // postcondition: the compare have been copied
    PriorityQueue(const Compare &_compare) : PriorityQueue(_compare, Container()) {}

    // name: parameterized constructor
    // precondition: the container have not been copied to _container
    // postcondition: the container have been copied
    PriorityQueue(const Container &_container) : PriorityQueue(Compare(), _container) {}

    // name: parameterized constructor
    // precondition: both compare and container have not been copied to _container and _compare
    // postcondition: both comapre and container have been copied to _container and _compare
    PriorityQueue(const Compare &_compare, const Container &_container) : compare(_compare), container(_container)
    {
        heapify(&container, compare);
    }

    // name: destructor
    // precondition: the priorityqueue has not been deleted
    // postcondition: the priorityQueue has been destroyed
    ~PriorityQueue() { make_empty(); }

    // name: copy assignment constructor
    // precondition: the priorityqueue has not been copied
    // postcondition: the priorityqueue has been copied
    PriorityQueue &operator=(const PriorityQueue &other)
    {
        if (&other == this)
        {
            return *this;
        }

        make_empty();
        container = other.container;
        compare = other.compare;

        return *this;
    }

    // name: top
    // precondition: We do not know the minimum element in the priority queue
    // postcondition: returns the minimum element in the priority queue
    const_reference top() const
    {
        return heap_get_min(container);
    }

    // name: empty
    // precondition: We do not know if the priority queue is empty
    // postcondition: returns true if the priority queue is empty and false otherwise
    bool empty() const
    {
        if (container.size() <= 1)
        {
            return true;
        }
        return false;
    }

    // name: size
    // precondition: we do not know the size of the priority queue
    // postcondition: returns the size of the priority queue
    size_type size() const // return size
    {
        if (container.size() <= 1)
        {
            return 0;
        }
        return container.size() - 1;
    }

    // name: make_empty
    // precondition: the priority queue is not empty
    // postcondition: erase all elements in the priority queue using clear()
    void make_empty()
    {
        container.clear();
    }

    // name: push
    // precondition: the value has not been pushed into the priority queue
    // postcondition: the value has been inserted into the priority queue
    void push(const value_type &value)
    {
        heap_insert(&container, value, compare);
    }

    // name: pop
    // precondition: the minimum value has not been removed from the priority queue
    // postcondition: the minimum value has been removed from the priority queue
    void pop()
    {
        heap_delete_min(&container, compare);
    }

    // name: print_queue
    // precondition: the values has not been printed pretty out to the console
    // postcondition: the values has been printed pretty out to the console
    void print_queue(std::ostream &os = std::cout) const
    {
        if (container.size() <= 1)
        {
            os << "<empty>\n";
        }

        for (size_t i = 0; i < container.size() - 1; i++)
        {
            os << container[i] << ", ";
        }
        os << container[container.size() - 1] << std::endl;
    }
};

#endif // PRIORITY_QUEUE_H