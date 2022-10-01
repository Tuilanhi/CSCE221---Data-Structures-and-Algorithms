#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <cstddef>
#include <stdexcept>

template <typename Object>
class ArrayList
{
private:
    // TODO(student): implement ArrayList
    // size of the array
    size_t array_size;
    // pointer to the array
    Object *arr;

public:
    ArrayList();
    ArrayList(std::size_t _capacity);
    ArrayList(const ArrayList &other);
    ~ArrayList();
    ArrayList &operator=(const ArrayList &other);
    size_t size() const;
    Object &operator[](std::size_t index);
    const Object &operator[](std::size_t index) const;
    void insert(size_t index, const Object &obj);
    void remove(size_t index);
};
// create and initialize an empty list
template <typename Object>
ArrayList<Object>::ArrayList()
{
    array_size = 0;
    arr = new Object[array_size];
}
// create and initialize a list with initial capacity
template <typename Object>
ArrayList<Object>::ArrayList(std::size_t _capacity)
{
    array_size = _capacity;
    arr = new Object[array_size];
}
// create and initialize a copy constructor
template <typename Object>
ArrayList<Object>::ArrayList(const ArrayList &other)
{
    array_size = other.size();
    arr = new Object[array_size];
    for (std::size_t i = 0; i < other.size(); i++)
    {
        arr[i] = other[i];
    }
}
// delete the list
template <typename Object>
ArrayList<Object>::~ArrayList()
{
    array_size = 0;
    delete arr;
}
// copy each element and index from orig list to the copied list
template <typename Object>
ArrayList<Object> &ArrayList<Object>::operator=(const ArrayList &other)
{
    // if it is a self copy
    if (&other == this)
    {
        return *this;
    }

    delete arr;
    array_size = other.size();
    arr = new Object[array_size];

    for (std::size_t i = 0; i < array_size; i++)
    {
        arr[i] = other[i];
    }

    return *this;
}
// returns the number of elements in the list
template <typename Object>
size_t ArrayList<Object>::size() const
{
    return array_size;
}
// returns a reference to the element at the specified index
template <typename Object>
Object &ArrayList<Object>::operator[](std::size_t index)
{
    if (index >= array_size || index < 0)
    {
        throw std::out_of_range("The index is out of bounds");
    }
    return arr[index];
}
// returns a reference to the element at the specified index that does not change
template <typename Object>
const Object &ArrayList<Object>::operator[](std::size_t index) const
{
    if (index < 0 || index >= array_size)
    {
        throw std::out_of_range("index out of range");
    }

    return arr[index];
}
// insert an object at the given index
template <typename Object>
void ArrayList<Object>::insert(size_t index, const Object &obj)
{
    if (index > array_size || index < 0)
    {
        throw std::out_of_range("The index is out of bounds");
    }

    // create a new Object temp that is 1 more the capacity of the arraylist
    Object *temp = new Object[array_size + 1];
    for (size_t i = 0; i < index; i++)
    {
        // std::move() is use to transfer resources from Object arr to Object temp
        temp[i] = std::move(arr[i]);
    }
    temp[index] = obj;

    for (size_t i = index; i < array_size; i++)
    {
        // shift everything to the right of the index right by + 1
        temp[i + 1] = std::move(arr[i]);
    }
    array_size++;
    delete arr;
    arr = temp;
}
// remove the object at the given index
template <typename Object>
void ArrayList<Object>::remove(size_t index)
{
    if (index >= array_size || index < 0 || array_size == 0)
    {
        throw std::out_of_range("The index is out of bounds");
    }

    // create a new Object with the size less than 1 of the orig array
    Object *temp = new Object[array_size - 1];

    for (size_t i = 0; i < index; i++)
    {
        // store the obj in arr at i to array temp at i
        temp[i] = std::move(arr[i]);
    }
    for (size_t i = index + 1; i < array_size; i++)
    {
        // at index + 1, store the obj in arr at i to temp at i - 1 (shifting the right of the index left)
        temp[i - 1] = std::move(arr[i]);
    }

    delete arr;
    arr = temp;
    // decrement the size of the array
    array_size--;
}

#endif // ARRAY_LIST_H
