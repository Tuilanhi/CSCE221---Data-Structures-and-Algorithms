#include <iostream>
#include "doubly_linked_list.h"

int main()
{
    // TODO(student): test your code
    DoublyLinkedList<int> double_linked_list;
    double_linked_list.insert(0, 1);
    double_linked_list.insert(1, 2);
    double_linked_list.insert(2, 3);
    double_linked_list.insert(3, 4);
    double_linked_list.insert(4, 5);
    std::cout << "The element at index 1 = " << double_linked_list[1] << std::endl;

    double_linked_list.insert(1, 24);
    std::cout << "The size of the linked list is = " << double_linked_list.size() << std::endl;
    std::cout << "The element at index 1 after inserting 24 at index 1 = " << double_linked_list[1] << std::endl;

    double_linked_list.remove(1);
    std::cout << "The element at index 1 after removing the element at index 1 = " << double_linked_list[1] << std::endl;
    std::cout << "The size of the linked list is = " << double_linked_list.size() << std::endl;
}
