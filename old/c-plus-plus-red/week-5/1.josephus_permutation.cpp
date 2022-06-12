#include <cstdint>
#include <iostream>
#include <iterator>
#include <list>
#include <numeric>
#include <vector>

#include "test_runner.h"

template <typename RandomIt>
void MakeJosephusPermutation(RandomIt first, RandomIt last, uint32_t step_size)
{
    std::list<typename RandomIt::value_type> pool;
    for (auto it = first; it != last; ++it)
    {
        pool.push_back(std::move(*it));
    }

    auto it_pos = pool.begin();
    size_t cur_pos = 0;
    while (!pool.empty())
    {
        *(first++) = std::move(*it_pos);

        it_pos = pool.erase(it_pos);
        if (pool.empty())
        {
            break;
        }
        auto next_pos = (cur_pos + step_size - 1) % pool.size();
        auto distance = next_pos - cur_pos;
        it_pos = std::next(it_pos, distance);
        cur_pos = next_pos;
    }
}

std::vector<int> MakeTestVector()
{
    std::vector<int> numbers(10);
    iota(begin(numbers), end(numbers), 0);
    return numbers;
}

void TestIntVector()
{
    const std::vector<int> numbers = MakeTestVector();
    {
        std::vector<int> numbers_copy = numbers;
        MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 1);
        ASSERT_EQUAL(numbers_copy, numbers);
    }
    {
        std::vector<int> numbers_copy = numbers;
        MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 3);
        ASSERT_EQUAL(numbers_copy, std::vector<int>({0, 3, 6, 9, 4, 8, 5, 2, 7, 1}));
    }
}

struct NoncopyableInt
{
    int value;

    NoncopyableInt(int value) : value(value)
    {
    }

    NoncopyableInt(const NoncopyableInt &) = delete;
    NoncopyableInt & operator=(const NoncopyableInt &) = delete;

    NoncopyableInt(NoncopyableInt &&) = default;
    NoncopyableInt & operator=(NoncopyableInt &&) = default;
};

bool operator==(const NoncopyableInt & lhs, const NoncopyableInt & rhs)
{
    return lhs.value == rhs.value;
}

std::ostream & operator<<(std::ostream & os, const NoncopyableInt & v)
{
    return os << v.value;
}

void TestAvoidsCopying()
{
    std::vector<NoncopyableInt> numbers;
    numbers.push_back({1});
    numbers.push_back({2});
    numbers.push_back({3});
    numbers.push_back({4});
    numbers.push_back({5});

    MakeJosephusPermutation(begin(numbers), end(numbers), 2);

    std::vector<NoncopyableInt> expected;
    expected.push_back({1});
    expected.push_back({3});
    expected.push_back({5});
    expected.push_back({4});
    expected.push_back({2});

    ASSERT_EQUAL(numbers, expected);
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestIntVector);
    RUN_TEST(tr, TestAvoidsCopying);
    return 0;
}
