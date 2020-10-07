#include <string_view>

bool IsPalindrom(const std::string_view &str) {
  for (int i = 0, j = str.size() - 1; i < j; ++i, --j) {
    if (str[i] != str[j]) {
      return false;
    }
  }
  return true;
}
