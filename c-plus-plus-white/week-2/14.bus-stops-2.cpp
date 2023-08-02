#include <iostream>
#include <map>
#include <string>
#include <vector>

int
main() {
  int cmd_count = 0;
  std::cin >> cmd_count;
  std::map<std::vector<std::string>, int> stops_num;
  for (int i = 0; i < cmd_count; ++i) {
    int stops_count = 0;
    std::cin >> stops_count;
    std::vector<std::string> stops(stops_count);
    for (auto &stop : stops) {
      std::cin >> stop;
    }
    if (stops_num.count(stops) == 0) {
      int route_num    = stops_num.size() + 1;
      stops_num[stops] = route_num;
      std::cout << "New bus " << route_num << std::endl;
    } else {
      std::cout << "Already exists for " << stops_num[stops] << std::endl;
    }
  }

  return 0;
}