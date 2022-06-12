#include <iostream>

struct a
{
    std::string s;
    uint64_t * a;
    uint16_t * c;
    uint8_t * b;
};

struct c
{
    std::string s;
    uint64_t a;
    uint16_t c;
    uint8_t b;
};

int main()
{
    auto b = sizeof(a), t = sizeof(c);
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
