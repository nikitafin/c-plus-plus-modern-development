#include <gtest/gtest.h>

import hash_set;

using namespace std;
using namespace modern_cxx::brown;

namespace modern_cxx::test
{


struct IntHasher
{
    size_t operator()(int value) const
    {
        // Это реальная хеш-функция из libc++, libstdc++.
        // Чтобы она работала хорошо, std::unordered_map
        // использует простые числа для числа бакетов
        return value;
    }
};

struct TestValue
{
    int value;

    bool operator==(TestValue other) const
    {
        return value / 2 == other.value / 2;
    }
};

struct TestValueHasher
{
    size_t operator()(TestValue value) const
    {
        return value.value / 2;
    }
};

TEST(HashSet, TestSmoke)
{
    HashSet<int, IntHasher> hash_set(2);
    hash_set.Add(3);
    hash_set.Add(4);

    ASSERT_TRUE(hash_set.Has(3));
    ASSERT_TRUE(!hash_set.Has(5));

    hash_set.Erase(3);

    ASSERT_TRUE(!hash_set.Has(3));
    ASSERT_TRUE(hash_set.Has(4));
    ASSERT_TRUE(!hash_set.Has(5));

    hash_set.Add(3);
    hash_set.Add(5);

    ASSERT_TRUE(hash_set.Has(3));
    ASSERT_TRUE(hash_set.Has(4));
    ASSERT_TRUE(hash_set.Has(5));
}

TEST(HashSet, TestEmpty)
{
    HashSet<int, IntHasher> hash_set(10);
    for (int value = 0; value < 10000; ++value)
    {
        ASSERT_TRUE(!hash_set.Has(value));
    }
}

TEST(HashSet, TestIdempotency)
{
    HashSet<int, IntHasher> hash_set(10);
    hash_set.Add(5);
    ASSERT_TRUE(hash_set.Has(5));
    hash_set.Add(5);
    ASSERT_TRUE(hash_set.Has(5));
    hash_set.Erase(5);
    ASSERT_TRUE(!hash_set.Has(5));
    hash_set.Erase(5);
    ASSERT_TRUE(!hash_set.Has(5));
}

TEST(HashSet, TestEquivalence)
{
    HashSet<TestValue, TestValueHasher> hash_set(10);
    hash_set.Add(TestValue{2});
    hash_set.Add(TestValue{3});

    ASSERT_TRUE(hash_set.Has(TestValue{2}));
    ASSERT_TRUE(hash_set.Has(TestValue{3}));

    const auto & bucket = hash_set.GetBucket(TestValue{2});
    const auto & three_bucket = hash_set.GetBucket(TestValue{3});
    ASSERT_EQ(&bucket, &three_bucket);

    ASSERT_EQ(1, distance(begin(bucket), end(bucket)));
    ASSERT_EQ(2, bucket.front().value);
}

}
