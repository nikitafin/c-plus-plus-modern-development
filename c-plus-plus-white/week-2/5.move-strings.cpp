#include <string>
#include <vector>

void
MoveStrings(std::vector<std::string> &source,
            std::vector<std::string> &destination) {
  for (auto &elem : source) {
    destination.push_back(elem);
  }
  source.clear();
}