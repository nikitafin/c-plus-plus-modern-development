#include <iostream>

int gcd(int fnum, int snum)
{
    if (snum > fnum)
    {
        std::swap(snum, fnum);
    }

    while (snum > 0)
    {
        int temp = fnum % snum;
        fnum = snum;
        snum = temp;
    }

    return fnum;
}

int main()
{
    int fnum = 0, snum = 0;
    std::cin >> fnum >> snum;

    std::cout << gcd(fnum, snum);

    return 0;
}