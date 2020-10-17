#include <set>
#include <vector>
#include <string>
#include <iostream>
#include <map>

int main() {
  int cmd_count = 0;
  std::cin >> cmd_count;
  std::map<std::set<std::string>, int> routes;
  for (int i = 0; i < cmd_count; ++i) {
    int stops_count = 0;
    std::cin >> stops_count;
    std::set<std::string> stops;
    for (int i = 0; i < stops_count; ++i) {
      std::string stop;
      std::cin >> stop;
      stops.insert(stop);
    }
    if (routes.count(stops) == 0) {
      int route_num = routes.size() + 1;
      routes[stops] = route_num;
      std::cout << "New bus " << route_num << std::endl;
    } else {
      std::cout << "Already exists for " << routes.at(stops) << std::endl;
    }
  }
  return 0;
}