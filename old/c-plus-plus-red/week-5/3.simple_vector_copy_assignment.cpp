#include <numeric>
#include <tuple>
#include <vector>

#include "simple_vector.h"
#include "test_runner.h"

const int SIZE = 10;

void TestCopyAssignment() {
  SimpleVector<int> numbers(SIZE);
  std::iota(numbers.begin(), numbers.end(), 1);

  SimpleVector<int> dest;
  ASSERT_EQUAL(dest.Size(), 0U);

  dest = numbers;
  ASSERT_EQUAL(dest.Size(), numbers.Size());
  ASSERT(dest.Capacity() >= dest.Size());
  ASSERT(std::equal(dest.begin(), dest.end(), numbers.begin()));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestCopyAssignment);
}
