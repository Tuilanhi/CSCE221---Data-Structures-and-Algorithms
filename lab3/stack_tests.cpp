#include <iostream>
#include "stack.h"

int main()
{
    // TODO(student): test your code
    Stack<int> stack;

    stack.push(1);
    stack.push(2);
    stack.push(3);

    std::cout << "The pop element is: " << stack.pop() << std::endl;
    std::cout << "The top of the stack is: " << stack.top() << std::endl;
    std::cout << "The size of the stack is: " << stack.size() << std::endl;

    stack.push(4);
    stack.push(5);
    stack.push(6);

    std::cout << "The top of the stack is: " << stack.top() << std::endl;
    std::cout << "The size of the stakc is: " << stack.size() << std::endl;
}
