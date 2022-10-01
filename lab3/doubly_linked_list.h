#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <cstddef>
#include <stdexcept>

template <typename Object>
class DoublyLinkedList
{
private:
    // TODO(student): implement DoublyLinkedList
    struct Node
    {
        Node *next;
        Node *prev;
        Object data;
    };

    Node *head;
    Node *tail;
    size_t list_size;

public:
    DoublyLinkedList();
    DoublyLinkedList(const DoublyLinkedList &other);
    ~DoublyLinkedList();
    DoublyLinkedList &operator=(const DoublyLinkedList &other);
    size_t size() const;
    Object &operator[](size_t index);
    void insert(size_t index, const Object &obj);
    void remove(size_t index);
    void insertAtBack(const Object &obj);
    void insertAtFront(const Object &obj);
    void clear_list();
};

// make an empty list
template <typename Object>
DoublyLinkedList<Object>::DoublyLinkedList()
{
    // set both head and tail as nullptr
    head = nullptr;
    tail = nullptr;
    list_size = 0;
}
// Construct a copy doublylinkedlist
template <typename Object>
DoublyLinkedList<Object>::DoublyLinkedList(const DoublyLinkedList &other)
{

    head = nullptr;
    tail = nullptr;
    list_size = 0;
    // create and initialize a temp Node and store the first node in it (head)
    Node *new_node = other.head;
    // loop until temp Node reaches the end of the list
    while (new_node != nullptr)
    {
        // insert the data from the back
        insertAtBack(new_node->data);
        new_node = new_node->next;
    }
    // reference the next node before deleting it
    delete new_node;
    // store the copied DoublyLinkedList size to lise_size
    list_size = other.size();
}

// delete the list
template <typename Object>
DoublyLinkedList<Object>::~DoublyLinkedList()
{
    clear_list();
}

// copy orig list into the created copy list
template <typename Object>
DoublyLinkedList<Object> &DoublyLinkedList<Object>::operator=(const DoublyLinkedList &other)
{
    // check if it is a self copied
    if (&other == this)
    {
        return *this;
    }

    clear_list();
    // create and initialize a temp Node and store the first node in it (head)
    Node *new_node = other.head;
    // loop until temp Node reaches the end of the list
    while (new_node != nullptr)
    {
        // insert the data from the back
        insertAtBack(new_node->data);
        new_node = new_node->next;
    }
    // reference the next node before deleting it
    delete new_node;
    // store the copied DoublyLinkedList size to lise_size
    list_size = other.size();
    return *this;
}

// returns the number of elements in the list
template <typename Object>
size_t DoublyLinkedList<Object>::size() const
{
    return list_size;
}

// returns a reference to the element at the specified index
template <typename Object>
Object &DoublyLinkedList<Object>::operator[](size_t index)
{
    // checks for out of bounds index
    if (index < 0 || index >= list_size)
    {
        throw std::out_of_range("The index is out of bounds");
    }

    // create and initialize a current index and set it to 0
    size_t current_index = 0;
    // create and initialize a new Node and set it to the first node
    Node *new_node = head;
    // loop until it reaches the end of the list
    while (new_node != nullptr)
    {
        if (current_index == index)
        {
            // exit loop
            break;
        }
        // store the address of the next node to new_node
        new_node = new_node->next;
        // incrementing current_index until it equals index
        current_index++;
    }

    return new_node->data;
}

// insert the given object at the specified index
template <typename Object>
void DoublyLinkedList<Object>::insert(size_t index, const Object &obj)
{
    // checks for index out of bounds
    if (index < 0 || index > list_size)
    {
        throw std::out_of_range("The index of out of bounds");
    }
    // checks to see if the index needs to be inserted at the beginning of the list, after the first node
    if (index == 0)
    {
        insertAtFront(obj);
    }
    // checks to see if the index needs to be inserted at the end of the list, before the nullptr
    else if (index == list_size)
    {
        insertAtBack(obj);
    }
    else
    {
        Node *new_node = new Node;
        // new_node stores the data for the item
        new_node->data = obj;
        size_t current_index = 0;
        // create and initialize a temp Node and equals the first node
        Node *temp = head;
        while (temp != nullptr)
        {
            // checks to see if the current_index equals index
            if (current_index == index)
            {
                // stores data at temp to the address of the next address of the new_node
                new_node->next = temp;
                // stores the address of the prev node of temp to the prev node of new_node
                new_node->prev = temp->prev;
                // stores the item at the next node of the prev node of new_node
                new_node->prev->next = new_node;
                // stores the item at the prev node of the next node of new_node
                new_node->next->prev = new_node;
                break;
            }
            // temp node stores the address of the next node
            temp = temp->next;
            current_index++;
        }
        // increment list_size every time an object is inserted
        list_size++;
    }
}

template <typename Object>
void DoublyLinkedList<Object>::remove(size_t index)
{
    // checks to see if index is out of bounds
    if (index < 0 || index >= list_size)
    {
        throw std::out_of_range("The index is out of bounds");
    }

    if (index == 0) // checks to see if the element needs to be removed at the beginning of the list after the first node
    {
        Node *temp = head;
        head = temp->next; // the first node equals the address store at the next node of temp Node
        list_size--;       // decrementing the list_size everytime an element is removed
        delete temp;
    }
    else if (index == list_size - 1) // checks to see if the element that needs to be removed is the last element of the list
    {
        tail = tail->prev;    // stores the address of the prev node to last node
        delete tail->next;    // delete the address of the next node to last node
        tail->next = nullptr; // set the address of the next node to the last node to a nullptr, indicating that it is the last node
        list_size--;          // decrementing the list_size everytime an element is removed
    }
    else
    {
        Node *temp = head;
        size_t current_index = 0;
        while (temp != nullptr)
        {
            if (current_index == index)
            {
                // stores the address of the next node to the prev node of temp to the next node of temp, skipping the node at index
                temp->prev->next = temp->next;
                // referencing the node before deleting it
                delete temp;
                list_size--;
                break;
            }
            temp = temp->next;
            current_index++;
        }
    }
}

template <typename Object>
void DoublyLinkedList<Object>::insertAtBack(const Object &obj)
{
    Node *new_node = new Node;
    new_node->data = obj;
    new_node->next = nullptr;

    if (head == nullptr)
    {
        new_node->prev = nullptr;
        head = new_node;
        tail = new_node;
    }
    else
    {
        new_node->prev = tail; // new_node will be the last node so tail node ->next points to new_node
        tail->next = new_node;
        tail = new_node;
    }
    list_size++;
}

template <typename Object>
void DoublyLinkedList<Object>::insertAtFront(const Object &obj)
{
    Node *new_node = new Node;
    new_node->data = obj;
    new_node->prev = nullptr;
    if (head == nullptr)
    {
        new_node->next = nullptr;
        head = new_node;
        tail = new_node;
    }
    else
    {
        // new_node will be the first node, so new_node->next points to head node
        new_node->next = head;
        head->prev = new_node;
        // head node becomes new node
        head = new_node;
    }
    list_size++;
}

template <typename Object>
void DoublyLinkedList<Object>::clear_list()
{
    Node *new_node = head;

    while (new_node != nullptr)
    {
        // creates a temp Node that points to the next node of new_node
        Node *temp = new_node->next;
        delete new_node;
        // assign the next node to the current node
        new_node = temp;
    }

    head = nullptr;
    tail = nullptr;
    list_size = 0;
}

#endif // DOUBLY_LINKED_LIST_H
