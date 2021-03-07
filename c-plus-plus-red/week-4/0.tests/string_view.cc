#include <array>
#include <iostream>
#include <string_view>

int main() {
  std::array<char, 10> arr = {'a', 'b', 'v', 'a', 'b', 'v', 'a', 'b', 'v', 'r'};

  std::string_view strw(arr.begin(), arr.size());
  std::cout << strw << std::endl;
  return 0;
}
