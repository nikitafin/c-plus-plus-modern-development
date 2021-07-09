#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshorten-64-to-32"
#pragma clang diagnostic ignored "-Wsign-conversion"

#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>

#include "test_runner.h"

using namespace std;

class ReadingManager {
public:
  ReadingManager() :
      pages_rating(MAX_PAGES_COUNT_ + 1, 0.0),
      user_pages(MAX_USER_COUNT_ + 1, 0),
      page_users(MAX_PAGES_COUNT_ + 1, 0),
      total_users(0) {}

  void Read(int user_id, int page_count) {
    if (user_pages[user_id] == 0) {
      ++total_users;
    } else {
      --page_users[user_pages[user_id]];
    }
    user_pages[user_id] = page_count;
    ++page_users[page_count];

    if (total_users == 1) {
      pages_rating[page_count] = 1.0;
    } else {
      int more_then = 0;
      int current_users = total_users;
      for (size_t i = 0; i < pages_rating.size() and current_users > 0; ++i) {
        while (i < pages_rating.size() and page_users[i] == 0) {
          ++i;
          pages_rating[i] = 0.0;
        }
        if (current_users == total_users) {
          pages_rating[i] = 0.0;
        } else if (current_users == 1) {
          pages_rating[i] = 1.0;
        } else {
          pages_rating[i] = more_then * 1.0 / (total_users - 1L);
        }
        current_users -= page_users[i];
        more_then += page_users[i];
      }
    }
  }

  double Cheer(int user_id) const {
    if (user_pages[user_id] == 0) {
      return 0.0;
    }
    if (total_users == 1) {
      return 1.0;
    }
    return pages_rating[user_pages[user_id]];
  }

private:
  std::vector<double> pages_rating;
  std::vector<int> user_pages;
  std::vector<int> page_users;

  static const int MAX_USER_COUNT_ = 100'000;
  static const int MAX_PAGES_COUNT_ = 1000;

  int total_users;
};

void TestBasic() {
  ReadingManager rm;
  ASSERT_EQUAL(rm.Cheer(5), 0.0);
  rm.Read(1, 10);
  ASSERT_EQUAL(rm.Cheer(1), 1.0);
  rm.Read(2, 5);
  rm.Read(3, 7);
  ASSERT_EQUAL(rm.Cheer(2), 0);
  ASSERT_EQUAL(rm.Cheer(3), 0.5);

  rm.Read(3, 10);
  ASSERT_EQUAL(rm.Cheer(3), 0.5);
  rm.Read(3, 11);
  ASSERT_EQUAL(rm.Cheer(3), 1);
  ASSERT_EQUAL(rm.Cheer(1), 0.5);
}

void Test0() {
  ReadingManager rm;
  rm.Read(1, 1);
  double a = rm.Cheer(1);
  rm.Read(2, 1);

  a = rm.Cheer(1);
  double b = rm.Cheer(2);

  rm.Read(3, 3);
  a = rm.Cheer(1);
  b = rm.Cheer(2);
  double c = rm.Cheer(3);

  rm.Read(4, 3);
  a = rm.Cheer(1);
  b = rm.Cheer(2);
  c = rm.Cheer(3);
  double d = rm.Cheer(4);

  rm.Read(5, 3);
  a = rm.Cheer(1);
  b = rm.Cheer(2);
  c = rm.Cheer(3);
  d = rm.Cheer(4);
  double e = rm.Cheer(5);

  rm.Read(6, 5);
  a = rm.Cheer(1);
  b = rm.Cheer(2);
  c = rm.Cheer(3);
  d = rm.Cheer(4);
  e = rm.Cheer(5);
  double f = rm.Cheer(6);

  return;
}

int main() {
  TestRunner tr;
  tr.RunTest(TestBasic, "Basics");
  tr.RunTest(Test0, "Test 0");

  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ReadingManager manager;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;
    int user_id;
    cin >> user_id;

    if (query_type == "READ") {
      int page_count;
      cin >> page_count;
      manager.Read(user_id, page_count);
    } else if (query_type == "CHEER") {
      cout << setprecision(6) << manager.Cheer(user_id) << "\n";
    }
  }

  return 0;

}
#pragma clang diagnostic pop