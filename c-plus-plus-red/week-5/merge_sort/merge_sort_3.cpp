#include "test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>

using namespace std;

template<typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
  if (range_begin + 1 == range_end) {
    return;
  }
  std::vector<typename RandomIt::value_type> v(make_move_iterator(range_begin), make_move_iterator(range_end));
  RandomIt b0 = v.begin();
  RandomIt b1 = b0 + v.size() / 3;
  RandomIt b2 = b1 + v.size() / 3;
  RandomIt b3 = v.end();

  MergeSort(b0, b1);
  MergeSort(b1, b2);
  MergeSort(b2, b3);

  std::vector<typename RandomIt::value_type> temp;

  std::merge(
      std::make_move_iterator(b0),
      std::make_move_iterator(b1),
      std::make_move_iterator(b1),
      std::make_move_iterator(b2),
      std::back_inserter(temp)
  );

  std::merge(
      std::make_move_iterator(temp.begin()),
      std::make_move_iterator(temp.end()),
      std::make_move_iterator(b2),
      std::make_move_iterator(b3),
      range_begin
  );
}

void TestIntVector() {
  vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
  MergeSort(begin(numbers), end(numbers));
  ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestIntVector);
  return 0;
}
