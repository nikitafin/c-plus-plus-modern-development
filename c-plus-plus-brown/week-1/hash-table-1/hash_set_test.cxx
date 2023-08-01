#include <gtest/gtest.h>

import hash_set;

using namespace std;
using namespace modern_cxx::brown;

namespace modern_cxx::test {

struct IntHasher {
  auto operator()(int Value) const -> size_t {
    // Это реальная хеш-функция из libc++, libstdc++.
    // Чтобы она работала хорошо, std::unordered_map
    // использует простые числа для количества бакетов.
    return Value;
  }
};

struct TestValue {
  int Value;

  auto operator==(TestValue Other) const -> bool {
    return Value / 2 == Other.Value / 2;
  }
};

struct TestValueHasher {
  auto operator()(TestValue Value) const -> size_t { return Value.Value / 2; }
};

TEST(HashSet, TestSmoke) {
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

TEST(HashSet, TestEmpty) {
  HashSet<int, IntHasher> hash_set(10);
  for (int Value = 0; Value < 10000; ++Value) {
    ASSERT_TRUE(!hash_set.Has(Value));
  }
}

TEST(HashSet, TestIdempotency) {
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

TEST(HashSet, TestEquivalence) {
  HashSet<TestValue, TestValueHasher> hash_set(10);
  hash_set.Add(TestValue{2});
  hash_set.Add(TestValue{3});

  ASSERT_TRUE(hash_set.Has(TestValue{2}));
  ASSERT_TRUE(hash_set.Has(TestValue{3}));

  const auto &bucket = hash_set.GetBucket(TestValue{2});
  const auto &three_bucket = hash_set.GetBucket(TestValue{3});
  ASSERT_EQ(&bucket, &three_bucket);

  ASSERT_EQ(1, distance(begin(bucket), end(bucket)));
  ASSERT_EQ(2, bucket.front().Value);
}

} // namespace modern_cxx::test
