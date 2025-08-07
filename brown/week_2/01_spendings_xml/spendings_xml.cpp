#include "xml.h"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

struct Spending {
  std::string category;
  int amount;
};

bool operator==(const Spending& lhs, const Spending& rhs) {
  return lhs.category == rhs.category && lhs.amount == rhs.amount;
}

std::ostream& operator<<(std::ostream& os, const Spending& s) {
  return os << '(' << s.category << ": " << s.amount << ')';
}

int CalculateTotalSpendings(const std::vector<Spending>& spendings) {
  int result = 0;
  for (const Spending& s : spendings) {
    result += s.amount;
  }
  return result;
}

std::string MostExpensiveCategory(const std::vector<Spending>& spendings) {
  auto compare_by_amount = [](const Spending& lhs, const Spending& rhs) {
    return lhs.amount < rhs.amount;
  };
  return max_element(begin(spendings), end(spendings), compare_by_amount)
      ->category;
}

std::vector<Spending> LoadFromXml(std::istream& input) {
  const Document document = Load(input);

  const Node& root = document.GetRoot();
  const std::vector<Node>& children = root.Children();

  std::vector<Spending> spendings;
  for (const Node& child : children) {
    std::string category = child.AttributeValue<std::string>("category");
    const int amount = child.AttributeValue<int>("amount");
    spendings.push_back({std::move(category), amount});
  }

  return spendings;
}

#if defined(WITH_TESTS)
#  include <gtest/gtest.h>

TEST(UnittestLoadFromXml, Smoke) {
  std::istringstream xml_input(R"(<july>
    <spend amount="2500" category="food"></spend>
    <spend amount="1150" category="transport"></spend>
    <spend amount="5780" category="restaurants"></spend>
    <spend amount="7500" category="clothes"></spend>
    <spend amount="23740" category="travel"></spend>
    <spend amount="12000" category="sport"></spend>
  </july>)");

  const std::vector<Spending> spendings = LoadFromXml(xml_input);

  const std::vector<Spending> expected = {
      {"food", 2500},    {"transport", 1150}, {"restaurants", 5780},
      {"clothes", 7500}, {"travel", 23740},   {"sport", 12000},
  };
  ASSERT_EQ(spendings, expected);
}

TEST(UnittestLoadFromXml, NoSpendings) {
  std::istringstream xml_input(R"(<july></july>)");

  std::vector<Spending> result = LoadFromXml(xml_input);
  EXPECT_TRUE(result.empty());
}

#endif
