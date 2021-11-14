#include <iostream>
#include <map>
#include <string>

std::map<char, int> BuildCharCount(const std::string &str) {
  std::map<char, int> result;
  for (const char &c: str) {
    ++result[c];
  }
  return result;
}

int main() {
  int row_count{0};
  std::string lhs, rhs;
  std::cin >> row_count;
  for (int i = 0; i < row_count; ++i) {
    std::cin >> lhs >> rhs;
    if (BuildCharCount(lhs) == BuildCharCount(rhs)) {
      std::cout << "YES" << std::endl;
    } else {
      std::cout << "NO" << std::endl;
    }
  }

  return 0;
}
