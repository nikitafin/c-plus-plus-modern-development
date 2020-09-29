#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main() {
  std::vector<std::string> vec(3);

  for (auto &str : vec) {
    std::cin >> str;
  }
  std::sort(std::begin(vec), std::end(vec));
  std::cout << vec.front() << std::endl;

  return 0;
}