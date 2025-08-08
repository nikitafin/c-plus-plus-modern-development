#include "ini.h"

#include <sstream>

#include <gtest/gtest.h>

using namespace std;

TEST(UnittestIni, LoadIni) {
  std::istringstream input(
      R"([july]
food=2500
sport=12000
travel=23400
clothes=5200

[august]
food=3250
sport=10000
travel=0
clothes=8300
jewelery=25000
)");

  const Ini::Document doc = Ini::Load(input);
  ASSERT_EQ(doc.SectionCount(), 2u);

  const Ini::Section expected_july = {
      {"food", "2500"},
      {"sport", "12000"},
      {"travel", "23400"},
      {"clothes", "5200"},
  };
  const Ini::Section expected_august = {
      {"food", "3250"},    {"sport", "10000"},    {"travel", "0"},
      {"clothes", "8300"}, {"jewelery", "25000"},
  };

  ASSERT_EQ(doc.GetSection("july"), expected_july);
  ASSERT_EQ(doc.GetSection("august"), expected_august);
}

TEST(UnittestIni, Document) {
  Ini::Document doc;
  ASSERT_EQ(doc.SectionCount(), 0U);

  // Обратите внимание, как мы используем указатель для работы
  // с последней добавленной секцией. Эта техника может вам пригодиться
  // для реализации функции Load
  Ini::Section *section = &doc.AddSection("one");
  ASSERT_EQ(doc.SectionCount(), 1U);

  section->insert({"name_1", "value_1"});
  section->insert({"name_2", "value_2"});

  section = &doc.AddSection("two");
  section->insert({"name_1", "value_1"});
  section->insert({"name_2", "value_2"});
  section->insert({"name_3", "value_3"});

  section = &doc.AddSection("three");
  section->insert({"name_1", "value_1"});

  ASSERT_EQ(doc.SectionCount(), 3U);
  const Ini::Section expected_one = {
      {"name_1", "value_1"},
      {"name_2", "value_2"},
  };
  const Ini::Section expected_two = {
      {"name_1", "value_1"},
      {"name_2", "value_2"},
      {"name_3", "value_3"},
  };
  const Ini::Section expected_three = {{"name_1", "value_1"}};

  ASSERT_EQ(doc.GetSection("one"), expected_one);
  ASSERT_EQ(doc.GetSection("two"), expected_two);
  ASSERT_EQ(doc.GetSection("three"), expected_three);
}

TEST(UnittestUni, UnknownSection) {
  Ini::Document doc;
  doc.AddSection("primary");

  ASSERT_THROW(doc.GetSection("secondary"), std::out_of_range);
}

TEST(UnittestIni, DuplicateSections) {
  Ini::Document doc;
  doc.AddSection("one").insert({"key_1", "value_1"});
  doc.AddSection("one").insert({"key_2", "value_2"});

  const Ini::Section expected = {{"key_1", "value_1"}, {"key_2", "value_2"}};
  ASSERT_EQ(doc.GetSection("one"), expected);
}
