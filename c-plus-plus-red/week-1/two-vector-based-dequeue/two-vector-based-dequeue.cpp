#include "dequeue.h"

int main()
{
    Deque<double> deque;
    deque.PushBack(123);
    deque.PushFront(-123);
    deque.PushBack(123);
    deque.PushFront(-123);
    deque.PushBack(123);
    deque.PushFront(-123);
    printf_s("123");
    return EXIT_SUCCESS;
}