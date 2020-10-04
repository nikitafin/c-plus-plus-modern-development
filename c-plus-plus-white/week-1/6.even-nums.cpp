#include <iostream>

int main() {
  int left = 0, right = 0;
  std::cin >> left >> right;
  for (int i = left; i <= right; ++i) {
    if (i % 2 == 0) {
      std::cout << i << " ";
    }
  }
  std::cout << std::endl;
  return 0;
}