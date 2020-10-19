#include <string>
#include <map>
#include <vector>

class Person {
 public:

  Person(const std::string &first_name, const std::string &last_name, int birth_year)
      : birth_year(birth_year), first_name_history{{birth_year, first_name}},
        last_name_history{{birth_year, last_name}} {}

  void ChangeFirstName(int year, const std::string &first_name) {
    if (year < birth_year) {
      return;
    }
    first_name_history[year] = first_name;
  }

  void ChangeLastName(int year, const std::string &last_name) {
    if (year < birth_year) {
      return;
    }
    last_name_history[year] = last_name;
  }

  std::string GetFullName(int year) const {
    if (year < birth_year) {
      return "No person";
    }
    std::string first_name = BuildFullName(year, first_name_history);
    std::string last_name = BuildFullName(year, last_name_history);

    if (first_name.empty() and last_name.empty()) {
      return "Incognito";
    } else if (!first_name.empty() and last_name.empty()) {
      return first_name + " with unknown last name";
    } else if (first_name.empty() and !last_name.empty()) {
      return last_name + " with unknown first name";
    } else {
      return first_name + " " + last_name;
    }
  }

  std::string GetFullNameWithHistory(int year) const {
    if (year < birth_year) {
      return "No person";
    }

    std::string first_name = BuildFullNameHistory(year, first_name_history);
    std::string last_name = BuildFullNameHistory(year, last_name_history);

    if (first_name.empty() and last_name.empty()) {
      return "Incognito";
    } else if (!first_name.empty() and last_name.empty()) {
      return first_name + " with unknown last name";
    } else if (first_name.empty() and !last_name.empty()) {
      return last_name + " with unknown first name";
    } else {
      return first_name + " " + last_name;
    }
  }

 private:
  std::string BuildFullName(int year, const std::map<int, std::string> &history) const {
    std::string result;
    for (const auto&[y, hist] : history) {
      if (y <= year) {
        result = hist;
      }
    }
    return result;
  }

  std::string BuildFullNameHistory(int year, const std::map<int, std::string> &history) const {

    std::vector<std::string> hist;
    for (const auto&[y, value] : history) {
      if (y <= year) {
        hist.push_back(value);
      }
    }

    std::string result;
    if (hist.empty()) {
      return result;
    } else if (hist.size() == 1) {
      result = hist.back();
      return result;
    } else {
      result = hist.back();
      std::string prev = hist.back();
      std::vector<std::string> temp;

      for (auto it = hist.rbegin(); it != hist.rend(); ++it) {
        if (*it != prev) {
          temp.push_back(*it);
        }
        prev = *it;
      }

      if (!temp.empty()) {
        result += " (";
        bool is_first = true;
        for (const auto &h : temp) {
          if (!is_first) {
            result += ", ";
          }
          is_first = false;
          result += h;
        }
        result += ")";
      }

      return result;
    }
  }

  int birth_year;
  std::map<int, std::string> first_name_history;
  std::map<int, std::string> last_name_history;
};