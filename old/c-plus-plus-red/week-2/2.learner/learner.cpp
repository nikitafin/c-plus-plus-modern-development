#include <algorithm>
#include <string>
#include <vector>
#include <set>

class Learner {
private:
  std::set<std::string> dictionary;

public:
  int Learn(const std::vector<std::string> &words) {
    int newWords = 0;
    for (const auto &word: words) {
      if (!dictionary.count(word)) {
        ++newWords;
        dictionary.insert(word);
      }
    }
    return newWords;
  }

  std::vector<std::string> KnownWords() {
    return {dictionary.begin(), dictionary.end()};
  }
};