#ifndef QUEUE_H
#define QUEUE_H

#include <cstddef>
#include <stdexcept>
#include "doubly_linked_list.h"

template <typename Object>
class Queue
{
private:
    // TODO(student): implement Queue
    DoublyLinkedList<Object> list;

public:
    Queue();
    Queue(const Queue &other);
    ~Queue();
    Queue &operator=(const Queue &other);
    void enqueue(const Object &item);
    Object dequeue();
    Object &front();
    size_t size() const;
};
// create and initialize an empty doublelinked list
template <typename Object>
Queue<Object>::Queue() : list() {}

// create a copy of the orig linked list
template <typename Object>
Queue<Object>::Queue(const Queue &other)
{
    list = other.list;
}

// create a decontructor of the linkedlist
template <typename Object>
Queue<Object>::~Queue()
{
    list.clear_list();
}
// create and copy the orig into the copied list
template <typename Object>
Queue<Object> &Queue<Object>::operator=(const Queue &other)
{
    // if it is a self copy
    if (&other == this)
    {
        return *this;
    }
    // if not copy the orig into the given one
    list = other.list;
    return *this;
}

// returns the number of elements in the queue
template <typename Object>
size_t Queue<Object>::size() const
{
    return list.size();
}

template <typename Object>
void Queue<Object>::enqueue(const Object &item)
{
    // adding the item in the back of the queue
    list.insertAtBack(item);
}

// remove the next value in the queue and return the item value
template <typename Object>
Object Queue<Object>::dequeue()
{
    if (list.size() == 0)
    {
        throw std::out_of_range("Queue size is 0");
    }

    // assign the front item into a new Object
    Object value = list[0];
    // remove the first item
    list.remove(0);

    return value;
}

// return a reference to the next item in queue
template <typename Object>
Object &Queue<Object>::front()
{
    if (list.size() == 0)
    {
        throw std::out_of_range("Queue size is 0");
    }

    return list[0];
}
#endif // QUEUE_H
