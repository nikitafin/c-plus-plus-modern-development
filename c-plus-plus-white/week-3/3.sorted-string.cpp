#include <string>
#include <algorithm>
#include <vector>

class SortedStrings {
public:
  void AddString(const std::string &str) {
    strs.push_back(str);
  }
  std::vector<std::string> GetSortedStrings() {
    std::sort(strs.begin(), strs.end());
    return strs;
  }
private:
  std::vector<std::string> strs;
};