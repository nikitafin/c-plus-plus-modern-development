#include <vector>

std::vector<int> Reversed(const std::vector<int> & vec)
{
    return {vec.rbegin(), vec.rend()};
}

int main()
{
    auto res = Reversed({1, 5, 3, 4, 2});

    return 0;
}