#include <iostream>
#include <vector>

int main() {
  int current_month = 0;
  std::vector<int> day_in_month = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  std::vector<std::vector<std::string>> list(day_in_month[current_month]);

  int Q;  // number of commands
  std::cin >> Q;
  for (int i = 0; i < Q; ++i) {
    std::string current_command;
    std::cin >> current_command;
    if (current_command == "ADD") {
      std::string task;
      int day;
      std::cin >> day >> task;
      list[day - 1].push_back(task);
    } else if (current_command == "DUMP") {
      int day;
      std::cin >> day;
      std::cout << list[day - 1].size() << " ";
      for (auto task : list[day - 1]) {
        std::cout << task << " ";
      }
      std::cout << endl;
    } else if (current_command == "NEXT") {
      int prev_month = current_month;
      current_month = (current_month + 1) % 12;
      int cur_d = day_in_month[current_month];
      int prev_d = day_in_month[prev_month];
      if (cur_d < prev_d) {
        for (int i = cur_d + 1; i <= prev_d; ++i) {
          if (!list[i - 1].empty()) {
            list[cur_d - 1].insert(end(list[cur_d - 1]), begin(list[i - 1]),
                                   end(list[i - 1]));
          }
        }
        list.resize(cur_d);
      } else {
        list.resize(cur_d);
      }
    }
  }

  return 0;
}