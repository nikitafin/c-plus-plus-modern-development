#include "json.h"

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
  return std::max_element(begin(spendings), end(spendings), compare_by_amount)
      ->category;
}

std::vector<Spending> LoadFromJson(std::istream& input) {
  const Document document = Load(input);
  const std::vector<Node>& entities = document.GetRoot().AsArray();

  std::vector<Spending> spendings;
  spendings.reserve(entities.size());
  for (const auto& entity : entities) {
    const std::map<std::string, Node>& record = entity.AsMap();
    std::string category = record.at("category").AsString();
    const int amount = record.at("amount").AsInt();

    spendings.push_back({std::move(category), amount});
  }

  return spendings;
}

#if defined(WITH_TESTS)
#  include <gtest/gtest.h>

TEST(UnittestLoadFromJson, Smoke) {
  std::istringstream json_input(R"([
    {"amount": 2500, "category": "food"},
    {"amount": 1150, "category": "transport"},
    {"amount": 5780, "category": "restaurants"},
    {"amount": 7500, "category": "clothes"},
    {"amount": 23740, "category": "travel"},
    {"amount": 12000, "category": "sport"}
  ])");

  const std::vector<Spending> spendings = LoadFromJson(json_input);

  const std::vector<Spending> expected = {
      {"food", 2500},    {"transport", 1150}, {"restaurants", 5780},
      {"clothes", 7500}, {"travel", 23740},   {"sport", 12000}};
  ASSERT_EQ(spendings, expected);
}

#endif