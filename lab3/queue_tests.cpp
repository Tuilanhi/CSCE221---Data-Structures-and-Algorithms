#include <iostream>
#include "queue.h"

int main()
{
    // TODO(student): test your code
    Queue<int> queue;

    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);

    std::cout << "The dequeue element is : " << queue.dequeue() << std::endl;
    std::cout << "The front element is : " << queue.front() << std::endl;

    queue.enqueue(4);
    queue.enqueue(5);
    queue.enqueue(6);

    queue.dequeue();

    std::cout << "The front element is : " << queue.front() << std::endl;
}
