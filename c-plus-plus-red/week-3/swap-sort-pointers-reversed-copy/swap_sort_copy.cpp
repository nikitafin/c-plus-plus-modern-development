#include "test_runner.h"

#include <algorithm>
#include <numeric>

template <typename T>
void
Swap(T *first, T *second) {
  std::swap(*first, *second);
}

template <typename T>
void
SortPointers(std::vector<T *> &pointers) {
  std::sort(pointers.begin(), pointers.end(),
            [](T *lhs, T *&rhs) { return *lhs < *rhs; });
}

template <typename T>
void
ReversedCopy(T *source, size_t count, T *destination) {
  if (destination > source + count || destination + count < source) {
    std::reverse_copy(source, source + count, destination);
  } else if (destination > source) {
    std::reverse_copy(source, destination, source + count);
    std::reverse(destination, source + count);
  } else {
    std::reverse_copy(destination + count, source + count, destination);
    std::reverse(source, destination + count);
  }
}

void
TestSwap() {
  int a = 1;
  int b = 2;
  Swap(&a, &b);
  ASSERT_EQUAL(a, 2);
  ASSERT_EQUAL(b, 1);

  std::string h = "world";
  std::string w = "hello";
  Swap(&h, &w);
  ASSERT_EQUAL(h, "hello");
  ASSERT_EQUAL(w, "world");
}

void
TestSortPointers() {
  int one   = 1;
  int two   = 2;
  int three = 3;

  std::vector<int *> pointers;
  pointers.push_back(&two);
  pointers.push_back(&three);
  pointers.push_back(&one);

  SortPointers(pointers);

  ASSERT_EQUAL(pointers.size(), 3u);
  ASSERT_EQUAL(*pointers[0], 1);
  ASSERT_EQUAL(*pointers[1], 2);
  ASSERT_EQUAL(*pointers[2], 3);
}

void
TestReverseCopy() {
  const size_t count = 7;

  int *source = new int[count];
  int *dest   = new int[count];

  for (size_t i = 0; i < count; ++i) {
    source[i] = i + 1;
  }
  ReversedCopy(source, count, dest);
  const std::vector<int> expected1 = {7, 6, 5, 4, 3, 2, 1};
  ASSERT_EQUAL(std::vector<int>(dest, dest + count), expected1);

  // Области памяти могут перекрываться
  ReversedCopy(source, count - 1, source + 1);
  const std::vector<int> expected2 = {1, 6, 5, 4, 3, 2, 1};
  ASSERT_EQUAL(std::vector<int>(source, source + count), expected2);

  delete[] dest;
  delete[] source;
}

int
main() {
  TestRunner tr;
  RUN_TEST(tr, TestSwap);
  RUN_TEST(tr, TestSortPointers);
  RUN_TEST(tr, TestReverseCopy);
  return 0;
}
