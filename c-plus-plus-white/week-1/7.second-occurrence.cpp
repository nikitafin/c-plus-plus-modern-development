#include <iostream>
#include <string>

int
main() {
  std::string str;
  std::cin >> str;
  int count_f = 0, idx_f = -1;
  for (int i = 0; i < str.size() and count_f < 2; ++i) {
    if (str[i] == 'f') {
      count_f += 1;
      idx_f = i;
    }
  }
  if (count_f >= 2) {
    std::cout << idx_f;
  } else if (count_f == 1) {
    std::cout << -1;
  } else {
    std::cout << -2;
  }
  return 0;
}