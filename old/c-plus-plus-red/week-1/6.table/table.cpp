#include "test_runner.h"

#include <utility>
#include <vector>

template<typename T>
class Table {
public:
  Table(size_t rows, size_t colls) : data(rows, std::vector<T>(colls)), rows(rows), colls(colls) {}

  void Resize(size_t ni, size_t nj) {
    data.resize(ni);
    rows = ni;
    for (auto &row: data) {
      row.resize(nj);
    }
    colls = nj;
  }

  std::pair<size_t, size_t> Size() const {
    return (rows == 0 or colls == 0) ?
           std::pair(0ul, 0ul) :
           std::pair(rows, colls);
  }

  std::vector<T> &operator[](size_t i) {
    return data[i];
  }

  std::vector<T> &operator[](size_t i) const {
    return data[i];
  }

private:
  std::vector<std::vector<T>> data;
  size_t rows, colls;
};

void TestTable() {
  Table<int> t(1, 1);
  ASSERT_EQUAL(t.Size().first, 1u)
  ASSERT_EQUAL(t.Size().second, 1u)
  t[0][0] = 42;
  ASSERT_EQUAL(t[0][0], 42);
  t.Resize(3, 4);
  ASSERT_EQUAL(t.Size().first, 3u);
  ASSERT_EQUAL(t.Size().second, 4u);

  Table<int> t2{1, 0};
  ASSERT_EQUAL(t2.Size().first, 0u)
  ASSERT_EQUAL(t2.Size().second, 0u)
  std::cout << t[1][0];
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestTable);
  return 0;
}
