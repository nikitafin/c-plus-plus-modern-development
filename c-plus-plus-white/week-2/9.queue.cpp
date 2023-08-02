#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

void
worry(std::vector<char> &queue, int idx) {
  queue.at(idx) = 'w';
}
void
quite(std::vector<char> &queue, int idx) {
  queue.at(idx) = 'q';
}
void
come(std::vector<char> &queue, int cnt) {
  if (cnt > 0) {
    for (int i = 0; i < cnt; ++i) {
      queue.push_back('q');
    }
  } else if (cnt < 0) {
    for (int i = 0; i < -cnt; ++i) {
      queue.pop_back();
    }
  }
}
int
worry_count(const std::vector<char> &queue) {
  return std::count(queue.begin(), queue.end(), 'w');
}

int
main() {
  int cmd_count = 0;
  std::vector<char> queue;
  std::cin >> cmd_count;
  for (int i = 0; i < cmd_count; ++i) {
    std::string cmd;
    std::cin >> cmd;
    if (cmd == "WORRY") {
      int w_cnt = 0;
      std::cin >> w_cnt;
      worry(queue, w_cnt);
    } else if (cmd == "QUIET") {
      int q_cnt = 0;
      std::cin >> q_cnt;
      quite(queue, q_cnt);
    } else if (cmd == "COME") {
      int come_cnt = 0;
      std::cin >> come_cnt;
      come(queue, come_cnt);
    } else {
      std::cout << worry_count(queue) << std::endl;
    }
  }

  return 0;
}