#include <vector>

void
Reverse(std::vector<int> &vec) {
  for (int i = 0, j = vec.size() - 1; i < j; i++, j--) {
    std::swap(vec.at(i), vec.at(j));
  }
}
//
// int main() {
//  std::vector<int> numbers = {1, 5, 3, 4, 2, 6};
//  Reverse(numbers);
//
//  return 0;
//}