#include <cassert>
#include <cstddef>
#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

template <typename Iterator>
class IteratorRange {
 public:
  IteratorRange(Iterator begin, Iterator end) : first_(begin), last_(end) {}
  Iterator begin() const { return first_; }
  Iterator end() const { return last_; }

 private:
  Iterator first_, last_;
};

template <typename Collection>
auto Head(Collection& collection, size_t top) {
  const auto count =
      static_cast<std::ptrdiff_t>(std::min(top, collection.size()));
  return IteratorRange{collection.begin(),
                       std::next(collection.begin(), count)};
}

struct Person {
  std::string name;
  int age, income;
  bool is_male;
};

bool operator<(const Person& lhs, const Person& rhs) {
  return lhs.age < rhs.age;
}

std::vector<Person> ReadPeople(std::istream& input) {
  int count;
  input >> count;

  assert(count > 0);

  std::vector<Person> result(static_cast<size_t>(count));
  for (Person& person : result) {
    char gender;
    input >> person.name >> person.age >> person.income >> gender;
    person.is_male = gender == 'M';
  }

  return result;
}

class PersonStats final {
 public:
  using Persons = std::vector<Person>;
  using Iterator = Persons::iterator;

  using PopularNameIndex = std::map<std::string_view, size_t>;

  explicit PersonStats(Persons persons)
      : persons_(std::move(persons)), persons_sorted_by_income_(persons_) {
    std::sort(persons_.begin(), persons_.end());

    std::sort(persons_sorted_by_income_.begin(),
              persons_sorted_by_income_.end(),
              [](const Person& lhs, const Person& rhs) {
                return lhs.income > rhs.income;
              });

    for (auto it = persons_.begin(); it != persons_.end(); ++it) {
      if (it->is_male) {
        auto& count = ++male_[it->name];
        if (count > most_popular_name_male_count_) {
          most_popular_name_male_ = it->name;
          most_popular_name_male_count_ = count;
        }
        if (count == most_popular_name_male_count_ and
            it->name.compare(most_popular_name_male_) < 0) {
          most_popular_name_male_ = it->name;
        }
      } else {
        auto& count = ++female_[it->name];
        if (count > most_popular_name_female_count_) {
          most_popular_name_female_ = it->name;
          most_popular_name_female_count_ = count;
        }
        if (count == most_popular_name_female_count_ and
            it->name.compare(most_popular_name_female_) < 0) {
          most_popular_name_female_ = it->name;
        }
      }
    }
  }

  int MaturityCount(int age_border) const {
    Person key = {"", age_border, 0, false};
    auto it = std::lower_bound(persons_.cbegin(), persons_.cend(), key);
    if (it == persons_.cend()) {
      return 0;
    }

    return static_cast<int>(persons_.cend() - it);
  }

  size_t CalculateWealthy(int person_count) const {
    assert(person_count > 0);
    size_t result = 0;
    for (auto&& persons :
         Head(persons_sorted_by_income_, static_cast<size_t>(person_count))) {
      result += static_cast<size_t>(persons.income);
    }
    return result;
  }

  std::optional<std::string> MostPopularMaleName() const {
    if (most_popular_name_male_count_ == 0) {
      return std::nullopt;
    }

    assert(!most_popular_name_male_.empty());
    return std::make_optional<std::string>(most_popular_name_male_);
  }

  std::optional<std::string> MostPopularFemaleName() const {
    if (most_popular_name_female_count_ == 0) {
      return std::nullopt;
    }

    assert(!most_popular_name_female_.empty());
    return std::make_optional<std::string>(most_popular_name_female_);
  }

 private:
  Persons persons_;
  Persons persons_sorted_by_income_;

  PopularNameIndex male_;
  std::string_view most_popular_name_male_;
  size_t most_popular_name_male_count_ = 0;

  PopularNameIndex female_;
  std::string_view most_popular_name_female_;
  size_t most_popular_name_female_count_ = 0;
};

#if defined(WITH_TESTS)
// NOLINTBEGIN (*-magic-numbers)
#  define DOCTEST_CONFIG_NO_MULTITHREADING
#  define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#  include <doctest/doctest.h>

TEST_SUITE("Demographics Indicators: Smoke") {
  const PersonStats stats = [] {
    std::vector<Person> persons = {
        {"Ivan", 25, 1000, true},         //
        {"Olga", 30, 623, false},         //
        {"Sergey", 24, 825, true},        //
        {"Maria", 42, 1254, false},       //
        {"Mikhail", 15, 215, true},       //
        {"Oleg", 18, 230, true},          //
        {"Denis", 53, 8965, true},        //
        {"Maxim", 37, 9050, true},        //
        {"Ivan", 47, 19050, true},        //
        {"Ivan", 17, 50, true},           //
        {"Olga", 23, 550, false},         //
        {"Anastasia", 29, 3000, false},   //
        {"Alexey", 31, 4500, true},       //
        {"Dmitry", 22, 1200, true},       //
        {"Svetlana", 35, 7000, false},    //
        {"Andrey", 40, 8000, true},       //
        {"Tatiana", 28, 3500, false},     //
        {"Vladimir", 50, 10000, true},    //
        {"Ekaterina", 26, 4000, false},   //
        {"Nikita", 19, 600, true},        //
        {"Yulia", 34, 5500, false},       //
        {"Pavel", 45, 9500, true},        //
        {"Irina", 39, 7200, false},       //
        {"Maria", 30, 3000, false},       //
        {"Maria", 25, 1500, false},       //
        {"Maria", 35, 4500, false},       //
        {"Maria", 40, 6000, false},       //
        {"Maria", 28, 2000, false},       //
        {"Anastasia", 29, 3000, false},   //
        {"Svetlana", 35, 7000, false},    //
        {"Tatiana", 28, 3500, false},     //
        {"Ekaterina", 26, 4000, false},   //
        {"Yulia", 34, 5500, false},       //
        {"Irina", 39, 7200, false},       //
        {"Anna", 22, 1800, false},        //
        {"Anna", 27, 3200, false},        //
        {"Anna", 33, 5000, false},        //
        {"Anna", 29, 4000, false},        //
        {"Anna", 31, 6000, false},        //
        {"Anna", 95, 10, false},          //
        {"Elena", 24, 2500, false},       //
        {"Elena", 26, 3500, false},       //
        {"Elena", 32, 4500, false},       //
        {"Elena", 38, 7000, false},       //
        {"Elena", 29, 3000, false},       //
        {"Ivan", 30, 3000, true},         //
        {"Ivan", 25, 1500, true},         //
        {"Ivan", 35, 4500, true},         //
        {"Ivan", 40, 6000, true},         //
        {"Ivan", 28, 2000, true},         //
        {"Alex", 22, 1800, true},         //
        {"Alex", 27, 3200, true},         //
        {"Alex", 33, 5000, true},         //
        {"Alex", 29, 4000, true},         //
        {"Alex", 31, 6000, true},         //
        {"Alex", 98, 6000, true},         //
        {"Alex", 93, 6000, true},         //
        {"Alex", 97, 6000, true},         //
        {"Dmitry", 24, 2500, true},       //
        {"Dmitry", 26, 3500, true},       //
        {"Dmitry", 32, 4500, true},       //
        {"Dmitry", 38, 7000, true},       //
        {"Dmitry", 29, 3000, true},       //
        {"Aboba", 16, 1'000'000, true},   //
        {"Aboba2", 96, 1'000'000, true},  //
    };
    // NOLINTEND (*-magic-numbers)
    std::sort(persons.begin(), persons.end());
    return PersonStats{std::move(persons)};
  }();

  TEST_CASE("Check MaturityCount" * doctest::timeout(100)) {
    SUBCASE("Age >= 18") {
      const int got = stats.MaturityCount(18);
      const int want = 62;
      CHECK(got == want);
    }
    SUBCASE("Age >= 25") {
      const int got = stats.MaturityCount(25);
      const int want = 53;

      CHECK(got == want);
    }
    SUBCASE("Age >= 99") {
      const int got = stats.MaturityCount(99);
      const int want = 0;

      CHECK(got == want);
    }
    SUBCASE("Age >= 40") {
      const int got = stats.MaturityCount(40);
      const int want = 13;

      CHECK(got == want);
    }
    SUBCASE("Age >= 90") {
      const int got = stats.MaturityCount(90);
      const int want = 5;

      CHECK(got == want);
    }
  }

  TEST_CASE("Calculate Wealthy" * doctest::timeout(100)) {
    SUBCASE("Top 1") {
      const size_t got = stats.CalculateWealthy(1);
      const size_t want = 1'000'000;
      CHECK(got == want);
    }
    SUBCASE("Top 2") {
      const size_t got = stats.CalculateWealthy(2);
      const size_t want = 2'000'000;
      CHECK(got == want);
    }
    SUBCASE("Top 3") {
      const size_t got = stats.CalculateWealthy(3);
      const size_t want = 2'000'000 + 19'050;
      CHECK(got == want);
    }
  }

  TEST_CASE("Most popular male name" * doctest::timeout(100)) {
    const std::string got = stats.MostPopularMaleName().value();
    const std::string want("Alex");
    CHECK(got == want);
  }

  TEST_CASE("Most popular female name" * doctest::timeout(100)) {
    const std::string got = stats.MostPopularFemaleName().value();
    const std::string want("Anna");
    CHECK(got == want);
  }
}

TEST_SUITE("Demographics Indicators: Empty Data") {
  const PersonStats stats = [] {
    std::vector<Person> persons;
    return PersonStats(std::move(persons));
  }();

  TEST_CASE("Age" * doctest::timeout(1)) {
    const int got = stats.MaturityCount(0);
    const int want = 0;
    CHECK(got == want);
  }
  TEST_CASE("Wealthy" * doctest::timeout(1)) {
    const size_t got = stats.CalculateWealthy(1'000'000);
    const size_t want = 0;
    CHECK(got == want);
  }
  TEST_CASE("Most popular male name" * doctest::timeout(1)) {
    const std::optional<std::string> got = stats.MostPopularMaleName();
    const std::optional<std::string> want = std::nullopt;
    CHECK(got == want);
  }

  TEST_CASE("Most popular female name" * doctest::timeout(100)) {
    const std::optional<std::string> got = stats.MostPopularFemaleName();
    const std::optional<std::string> want = std::nullopt;
    CHECK(got == want);
  }
}

TEST_SUITE("Demographics Indicators: Popular Name") {
  const PersonStats stats = [] {
    std::vector<Person> persons = {
        {"aa", 10, 10, true},  {"aa", 10, 10, true},  {"aa", 10, 10, true},
        {"aa", 10, 10, true},  {"aa", 10, 10, true},

        {"aaa", 10, 10, true}, {"aaa", 10, 10, true}, {"aaa", 10, 10, true},
        {"aaa", 10, 10, true}, {"aaa", 10, 10, true},
    };
    std::sort(persons.begin(), persons.end());
    return PersonStats(std::move(persons));
  }();

  TEST_CASE("Aboba") {
    const std::string got = stats.MostPopularMaleName().value();
    const std::string want = "aa";
    CHECK(got == want);
  }
}

#else

int main() {
  const PersonStats stats = [] {
    std::vector<Person> people = ReadPeople(std::cin);
    std::sort(std::begin(people), std::end(people));
    return PersonStats(std::move(people));
  }();

  for (std::string command; std::cin >> command;) {
    if (command == "AGE") {
      int adult_age;
      std::cin >> adult_age;
      std::cout << "There are " << stats.MaturityCount(adult_age)
                << " adult people for maturity age " << adult_age << '\n';
    } else if (command == "WEALTHY") {
      int count;
      std::cin >> count;
      assert(count > 0);
      std::cout << "Top-" << count << " people have total income "
                << stats.CalculateWealthy(count) << '\n';
    } else if (command == "POPULAR_NAME") {
      char gender;
      std::cin >> gender;

      const std::optional<std::string> name = [gender, &stats] {
        if (gender == 'M') {
          return stats.MostPopularMaleName();
        }
        return stats.MostPopularFemaleName();
      }();
      if (!name) {
        std::cout << "No people of gender " << gender << '\n';
        continue;
      }
      std::cout << "Most popular name among people of gender " << gender
                << " is " << *name << '\n';
    }
  }
}
#endif