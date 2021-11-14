#include <map>
#include <string>
#include <iostream>

void ChangeCapital(std::map<std::string, std::string> &countries,
                   const std::string &country,
                   const std::string &capital) {
  if (countries.count(country) == 0) {
    std::cout << "Introduce new country " << country << " with capital " << capital << std::endl;
  } else if (countries[country] == capital) {
    std::cout << "Country " << country << " hasn't changed its capital" << std::endl;
  } else {
    std::cout << "Country " << country << " has changed its capital from " << countries[country]
              << " to " << capital
              << std::endl;
  }
  countries[country] = capital;
}

void Rename(std::map<std::string, std::string> &countries,
            const std::string &old_country_name,
            const std::string &new_country_name) {
  if (countries.count(old_country_name) == 0 or countries.count(new_country_name) == 1) {
    std::cout << "Incorrect rename, skip" << std::endl;
  } else {
    std::string capital = countries[old_country_name];
    countries.erase(old_country_name);
    countries[new_country_name] = capital;
    std::cout << "Country " << old_country_name << " with capital " << capital
              << " has been renamed to "
              << new_country_name << std::endl;
  }
}

void About(std::map<std::string, std::string> &countries, const std::string &country) {
  if (countries.count(country) == 0) {
    std::cout << "Country " << country << " doesn't exist" << std::endl;
  } else {
    std::cout << "Country " << country << " has capital " << countries[country] << std::endl;
  }
}

void Dump(std::map<std::string, std::string> &countries) {
  if (countries.empty()) {
    std::cout << "There are no countries in the world" << std::endl;
  } else {
    for (const auto&[country, capital]: countries) {
      std::cout << country << "/" << capital << " ";
    }
    std::cout << std::endl;
  }
}

int main() {
  int cmd_count{0};
  std::cin >> cmd_count;
  std::map<std::string, std::string> countries;
  for (int i = 0; i < cmd_count; ++i) {
    std::string current_cmd;
    std::cin >> current_cmd;
    if (current_cmd == "CHANGE_CAPITAL") {
      std::string country, new_capital;
      std::cin >> country >> new_capital;
      ChangeCapital(countries, country, new_capital);
    } else if (current_cmd == "RENAME") {
      std::string old_capital_name, new_capital_name;
      std::cin >> old_capital_name >> new_capital_name;
      Rename(countries, old_capital_name, new_capital_name);
    } else if (current_cmd == "ABOUT") {
      std::string country;
      std::cin >> country;
      About(countries, country);
    } else {
      Dump(countries);
    }
  }

  return 0;
}