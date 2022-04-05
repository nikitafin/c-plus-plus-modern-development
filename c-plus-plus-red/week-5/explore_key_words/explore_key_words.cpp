#include "profile.h"
#include "test_runner.h"

#include <functional>
#include <future>
#include <iterator>
#include <map>
#include <string>
#include <thread>

template<typename Iterator>
class Page
{
private:
  Iterator first, last;

public:
  Page(Iterator first, Iterator last)
    : first(first)
    , last(last)
  {}
  size_t size() const { return std::distance(first, last); }
  auto begin() { return first; }
  auto end() { return last; }
  auto begin() const { return first; }
  auto end() const { return last; }
};

template<typename Iterator>
class Paginator
{
public:
  Paginator(Iterator begin, Iterator end, size_t page_size)
  {
    size_t container_size = std::distance(begin, end);
    do {
      auto page_end = std::next(begin, std::min(page_size, container_size));
      if (begin != page_end) {
        elements.push_back({ begin, page_end });
      }
      begin = page_end;
      container_size -= std::min(page_size, container_size);
    } while (container_size > 0);
  }
  size_t size() const { return elements.size(); }

  auto begin() { return elements.begin(); }
  auto end() { return elements.end(); }

  auto begin() const { return elements.cbegin(); }
  auto end() const { return elements.cend(); }

private:
  std::vector<Page<Iterator>> elements;
};

struct Stats
{
  std::map<std::string, int> word_frequences;

  void operator+=(const Stats& other)
  {
    for (const auto& [word, count] : other.word_frequences) {
      word_frequences[word] += count;
    }
  }
};

template<typename T>
Stats
ExploreKeyWordsSingleThread(const T& t, const std::set<std::string>& key_words)
{
  Stats stats;
  for (const auto& s : t) {
    if (key_words.count(s)) {
      ++stats.word_frequences[s];
    }
  }
  return stats;
}

Stats
ExploreKeyWords(const std::set<std::string>& key_words, std::istream& input)
{
  std::vector<std::string> v(
    std::make_move_iterator(std::istream_iterator<std::string>(input)),
    std::make_move_iterator(std::istream_iterator<std::string>()));

  Stats result;
  std::vector<std::future<Stats>> futures;
  for (auto page : Paginator(
         v.begin(), v.end(), v.size() / std::thread::hardware_concurrency())) {
    futures.push_back(std::async(
      [=]() { return ExploreKeyWordsSingleThread(page, key_words); }));
  }

  for (auto& f : futures) {
    result += f.get();
  }

  return result;
}

void
TestBasic()
{
  const std::set<std::string> key_words = { "yangle", "rocks", "sucks", "all" };

  std::stringstream ss;
  ss << "this new yangle service really rocks\n";
  ss << "It sucks when yangle isn't available\n";
  ss << "10 reasons why yangle is the best IT company\n";
  ss << "yangle rocks others suck\n";
  ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

  const auto stats = ExploreKeyWords(key_words, ss);
  const std::map<std::string, int> expected = { { "yangle", 6 },
                                                { "rocks", 2 },
                                                { "sucks", 1 } };
  ASSERT_EQUAL(stats.word_frequences, expected);
}

int
main()
{
  TestRunner tr;
  RUN_TEST(tr, TestBasic);
}
