#include <unordered_set>
#include <unordered_map>
#include <list>
#include <iostream>
#include <algorithm>

class SportsmanManager {
private:
  std::unordered_map<int, std::list<int>::iterator> sportsman_num;
  std::list<int> sportsmans;
public:
  SportsmanManager();
  void Add(int new_sportsman, int next_sportsman);
  void Print(std::ostream &os);
};

SportsmanManager::SportsmanManager() : sportsman_num(), sportsmans() {}

void SportsmanManager::Add(int new_sportsman, int next_sportsman) {
  if (!sportsman_num.count(next_sportsman)) {
    auto it = sportsmans.insert(sportsmans.end(), new_sportsman);
    sportsman_num[new_sportsman] = it;
  } else {
    auto it = sportsmans.insert(sportsman_num[next_sportsman], new_sportsman);
    sportsman_num[new_sportsman] = it;
  }
}

void SportsmanManager::Print(std::ostream &os) {
  for (const auto &sportsman : sportsmans) {
    os << sportsman << "\n";
  }
  os << std::endl;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int count{0};
  SportsmanManager sm;
  std::cin >> count;
  for (int i = 0; i < count; ++i) {
    int new_s{0}, next_s{0};
    std::cin >> new_s >> next_s;
    sm.Add(new_s, next_s);
  }
  sm.Print(std::cout);
}