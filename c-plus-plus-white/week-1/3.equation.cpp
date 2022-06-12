#include <cmath>
#include <iostream>

int main()
{
    double a_coef = 0, b_coef = 0, c_coef = 0;
    std::cin >> a_coef >> b_coef >> c_coef;

    if (a_coef == 0)
    {
        if (b_coef == 0)
        {
            std::cout << std::endl;
        }
        else
        {
            std::cout << -c_coef / b_coef << std::endl;
        }
    }
    else
    {
        double d = b_coef * b_coef - 4.0 * a_coef * c_coef;
        if (d < 0)
        {
            std::cout << std::endl;
        }
        else if (d == 0)
        {
            std::cout << -b_coef / (2 * a_coef) << std::endl;
        }
        else
        {
            std::cout << (-b_coef + std::sqrt(d)) / (2 * a_coef) << " "
                      << (-b_coef - std::sqrt(d)) / (2 * a_coef) << std::endl;
        }
    }

    return 0;
}
/*
 * Tests
 * 1 5 4 -> -1 -4
 * 1 -5 4 -> 1 4
 * 0 0 1 -> ' '
 * 0 1 1 -> -1
 * 0 1 -1 -> 1
 * 0 -1 1 -> 1
 * 0 -1 -1 -> -1
 * 0 1 0 -> 0
 * 1 0 0 -> 0
 *
 *
 */