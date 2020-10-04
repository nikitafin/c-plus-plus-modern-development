#include <iostream>
#include <vector>

int main() {
  int number = 0;
  std::cin >> number;
  std::vector<int> bdigits;
  while (number > 0) {
    bdigits.push_back(number & 1);
    number >>= 1;
  }
  for (int i = bdigits.size() - 1; i >= 0; --i) {
    std::cout << bdigits[i];
  }

  return 0;
}