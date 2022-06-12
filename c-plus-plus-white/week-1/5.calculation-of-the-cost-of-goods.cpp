#include <iostream>

int main()
{
    float n = 0.f, a = 0.f, b = 0.f, x = 0.f, y = 0.f;
    std::cin >> n >> a >> b >> x >> y;
    float discount = 0.f;
    if (n > a)
    {
        discount = (n * x) / 100.f;
    }
    if (n > b)
    {
        discount = (n * y) / 100.f;
    }
    std::cout << (n - discount) << std::endl;

    return 0;
}