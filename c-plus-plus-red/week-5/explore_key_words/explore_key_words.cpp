#include "profile.h"
#include "test_runner.h"

#include <map>
#include <string>

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

Stats
ExploreKeyWords(const std::set<std::string>& key_words, std::istream& input)
{
  return {};
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
