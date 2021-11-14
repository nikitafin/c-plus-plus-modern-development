#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>

std::string to_lower(std::string str) {
  for (char &c: str) {
    c = std::tolower(c);
  }
  return str;
}

int main() {
  int str_count = 0;
  std::cin >> str_count;
  std::vector<std::string> str_container(str_count);
  for (auto &str: str_container) {
    std::cin >> str;
  }
  std::sort(str_container.begin(), str_container.end(), [](const auto &lhs, const auto &rhs) {
    return to_lower(lhs) < to_lower(rhs);
  });
  for (const auto &str: str_container) {
    std::cout << str << " ";
  }

  return 0;
}