#include <string>
#include <set>
#include <map>
#include <iostream>

using syns = std::map<std::string, std::set<std::string>>;

void Add(syns &synonyms, const std::string &f_word, const std::string &s_word) {
  synonyms[f_word].insert(s_word);
  synonyms[s_word].insert(f_word);
}
void Count(const syns &synonyms, const std::string &word) {
  if (synonyms.count(word) == 0) {
    std::cout << "0" << std::endl;
  } else {
    std::cout << synonyms.at(word).size() << std::endl;
  }
}
void Check(const syns &synonyms, const std::string &f_word, const std::string &s_word) {
  if (synonyms.count(f_word) and synonyms.at(f_word).count(s_word) != 0) {
    std::cout << "YES" << std::endl;
  } else {
    std::cout << "NO" << std::endl;
  }
}

int main() {
  syns synonyms;
  int cmd_count = 0;
  std::cin >> cmd_count;
  for (int i = 0; i < cmd_count; ++i) {
    std::string cmd;
    std::cin >> cmd;
    if (cmd == "ADD") {
      std::string f_word, s_word;
      std::cin >> f_word >> s_word;
      Add(synonyms, f_word, s_word);
    } else if (cmd == "CHECK") {
      std::string f_word, s_word;
      std::cin >> f_word >> s_word;
      Check(synonyms, f_word, s_word);
    } else {
      std::string word;
      std::cin >> word;
      Count(synonyms, word);
    }
  }

  return 0;
}