#include <vector>
#include <string>
#include <iostream>

int main() {
  std::vector<std::vector<std::string>> tasks(32);
  int operations_cnt = 0;
  int current_month = 1;
  std::cin >> operations_cnt;
  for (int i = 0; i < operations_cnt; ++i) {
    std::string cmd;
    std::cin >> cmd;
    if (cmd == "ADD") {
      int idx = 1;
      std::string task;
      std::cin >> idx >> task;
      tasks[idx].push_back(task);
    } else if (cmd == "DUMP") {
      int idx = 1;
      std::cin >> idx;
      std::cout << tasks[idx].size() << " ";
      for (const auto &task : tasks[idx]) {
        std::cout << task << " ";
      }
      std::cout << std::endl;
    } else {
      current_month = (current_month + 1) % 13;
      if (current_month == 1 or current_month == 3 or
          current_month == 5 or current_month == 7 or
          current_month == 8 or current_month == 12) {
        tasks.resize(32);
      } else if (current_month == 4 or current_month == 6
          or current_month == 9 or current_month == 11) {
        std::vector<std::string> last = tasks.back();
        tasks.resize(31);
        for (const auto &elem : last) {
          tasks.back().push_back(elem);
        }
      } else {
        std::vector<std::string> last = tasks.back();
        std::vector<std::string> prev_last = tasks[tasks.size() - 2];
        tasks.resize(29);
        for (const auto &elem : prev_last) {
          tasks.back().push_back(elem);
        }
        for (const auto &elem : last) {
          tasks.back().push_back(elem);
        }
      }
    }
  }
  return 0;
}