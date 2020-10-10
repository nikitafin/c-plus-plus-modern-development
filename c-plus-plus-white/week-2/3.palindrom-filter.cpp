#include <string_view>
#include <vector>
#include <string>

bool IsPalindrom(const std::string &str) {
  for (int i = 0, j = str.size() - 1; i < j; ++i, --j) {
    if (str[i] != str[j]) {
      return false;
    }
  }
  return true;
}

std::vector<std::string> PalindromFilter(const std::vector<std::string> &words, int min_length) {
  std::vector<std::string> result;
  for (const auto &word : words) {
    if (IsPalindrom(word) and word.size() >= min_length) {
      result.push_back(word);
    }
  }

  return result;
}

int main(){
  std::vector<std::string> words {"weew", "bro", "code"};
  auto res = PalindromFilter(words, 	4);

  return 0;
}