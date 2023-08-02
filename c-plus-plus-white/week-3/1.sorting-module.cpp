#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

int
main() {
  int elem_count = 0;
  std::cin >> elem_count;
  std::vector<int> input_vec(elem_count);
  for (auto &elem : input_vec) {
    std::cin >> elem;
  }
  std::sort(input_vec.begin(), input_vec.end(),
            [](int lhs, int rhs) { return std::abs(lhs) < std::abs(rhs); });

  for (const auto &elem : input_vec) {
    std::cout << elem << " ";
  }

  return 0;
}