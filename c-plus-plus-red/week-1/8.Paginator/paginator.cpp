#include "test_runner.h"

#include <numeric>
#include <iostream>
#include <vector>
#include <string>

template<typename Iterator>
class Page {
private:
  Iterator first, last;
public:
  Page(Iterator begin, Iterator end);
  size_t size() const;
  Iterator begin() const;
  Iterator end() const;
};

template<typename Iterator>
Page<Iterator>::Page(Iterator begin, Iterator end): first(begin), last(end) {}
template<typename Iterator>
size_t Page<Iterator>::size() const {
  return std::distance(first, last);
}
template<typename Iterator>
Iterator Page<Iterator>::begin() const {
  return first;
}
template<typename Iterator>
Iterator Page<Iterator>::end() const {
  return last;
}

template<typename Iterator>
class Paginator {
  std::vector<Page<Iterator>> pages;
  size_t pageSize, pageCount;
public:
  Paginator(Iterator begin, Iterator end, size_t pageSize);
  size_t size() const;
  auto begin() const;
  auto end() const;
};

template<typename Iterator>
Paginator<Iterator>::Paginator(Iterator begin, Iterator end, size_t page_size) {
  size_t length = static_cast<size_t>(std::distance(begin, end));
  for (auto temp = begin, nextTemp = std::next(temp, std::min(length, page_size));
       temp != end;
       temp = nextTemp, nextTemp = std::next(temp, std::min(length, page_size))) {
    length = length < page_size ? length : length - page_size;
    pages.push_back({temp, nextTemp});
  }
  pageSize = page_size;
  pageCount = pages.size();
}
template<typename Iterator>
size_t Paginator<Iterator>::size() const {
  return pageCount;
}
template<typename Iterator>
auto Paginator<Iterator>::begin() const {
  return pages.begin();
}
template<typename Iterator>
auto Paginator<Iterator>::end() const {
  return pages.end();
}

template<typename Container>
auto Paginate(Container &container, size_t pageSize) {
  return Paginator(container.begin(), container.end(), pageSize);
}

void TestPageCounts() {
  std::vector<int> v(15);

  auto t = Paginate(v, 4);

  ASSERT_EQUAL(Paginate(v, 1).size(), v.size());
  ASSERT_EQUAL(Paginate(v, 3).size(), 5u);
  ASSERT_EQUAL(Paginate(v, 5).size(), 3u);
  ASSERT_EQUAL(Paginate(v, 4).size(), 4u);
  ASSERT_EQUAL(Paginate(v, 15).size(), 1u);
  ASSERT_EQUAL(Paginate(v, 150).size(), 1u);
  ASSERT_EQUAL(Paginate(v, 14).size(), 2u);
}

void TestLooping() {
  std::vector<int> v(15);
  std::iota(v.begin(), v.end(), 1);

  Paginator<std::vector<int>::iterator> paginate_v(v.begin(), v.end(), 6);
  std::ostringstream os;
  for (const auto &page : paginate_v) {
    for (int x : page) {
      os << x << ' ';
    }
    os << '\n';
  }

  ASSERT_EQUAL(os.str(), "1 2 3 4 5 6 \n7 8 9 10 11 12 \n13 14 15 \n");
}

void TestModification() {
  std::vector<std::string> vs = {"one", "two", "three", "four", "five"};
  for (auto page : Paginate(vs, 2)) {
    for (auto &word : page) {
      word[0] = toupper(word[0]);
    }
  }

  const std::vector<std::string> expected = {"One", "Two", "Three", "Four", "Five"};
  ASSERT_EQUAL(vs, expected);
}

void TestPageSizes() {
  std::string letters(26, ' ');

  Paginator letters_pagination(letters.begin(), letters.end(), 11);
  std::vector<size_t> page_sizes;
  for (const auto &page : letters_pagination) {
    page_sizes.push_back(page.size());
  }

  const std::vector<size_t> expected = {11, 11, 4};
  ASSERT_EQUAL(page_sizes, expected);
}

void TestConstContainer() {
  const std::string letters = "abcdefghijklmnopqrstuvwxyz";

  std::vector<std::string> pages;
  for (const auto &page : Paginate(letters, 10)) {
    pages.push_back(std::string(page.begin(), page.end()));
  }

  const std::vector<std::string> expected = {"abcdefghij", "klmnopqrst", "uvwxyz"};
  ASSERT_EQUAL(pages, expected);
}

void TestPagePagination() {
  std::vector<int> v(22);
  iota(v.begin(), v.end(), 1);

  std::vector<std::vector<int>> lines;
  for (const auto &split_by_9 : Paginate(v, 9)) {
    for (const auto &split_by_4 : Paginate(split_by_9, 4)) {
      lines.push_back({});
      for (int item : split_by_4) {
        lines.back().push_back(item);
      }
    }
  }

  const std::vector<std::vector<int>> expected = {
      {1, 2, 3, 4},
      {5, 6, 7, 8},
      {9},
      {10, 11, 12, 13},
      {14, 15, 16, 17},
      {18},
      {19, 20, 21, 22}
  };
  ASSERT_EQUAL(lines, expected);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestPageCounts);
  RUN_TEST(tr, TestLooping);
  RUN_TEST(tr, TestModification);
  RUN_TEST(tr, TestPageSizes);
  RUN_TEST(tr, TestConstContainer);
  RUN_TEST(tr, TestPagePagination);
  return 0;
}

