#include <iostream>
#include "array_list.h"

int main()
{
    // TODO(student): test your code
    // create a new array called list
    ArrayList<int> list;

    list.insert(0, 1);
    list.insert(1, 25);
    list.insert(2, 45);

    std::cout << "Index at 2 = " << list[2] << std::endl;

    list.insert(3, 100);
    list.insert(4, 123);
    list.insert(5, 12);
    list.insert(2, 15); // replace index at 2 with 15

    std::cout << "Current list size = " << list.size() << std::endl;

    int value = list[2];
    std::cout << "Index at 2 = " << value << std::endl;

    list.remove(2);

    std::cout << "Index at 2 = " << list[2] << std::endl; // after remove index at 2, it is replaced with whatever is located at index at 3

    std::cout << "Current list size = " << list.size() << std::endl;
}
