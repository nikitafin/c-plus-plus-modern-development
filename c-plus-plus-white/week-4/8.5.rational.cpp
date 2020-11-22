#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <vector>

class Rational {
 public:
  Rational() : numerator(0), denominator(1) {}
  Rational(int newNumerator, int newDenominator) {
    if (newNumerator == 0) {
      numerator = 0;
      denominator = 1;
    } else {
      int sign = ((newNumerator > 0 && newDenominator > 0) || (newNumerator < 0 && newDenominator < 0)) ? 1 : -1;
      int gcd = std::gcd(newNumerator, newDenominator);
      numerator = std::abs(newNumerator / gcd);
      numerator *= sign;
      denominator = std::abs(newDenominator / gcd);
    }
  }

  int Numerator() const { return numerator; }
  int Denominator() const { return denominator; }

 private:
  int numerator;
  int denominator;
};

bool operator==(const Rational& lhs, const Rational& rhs) {
  return lhs.Numerator() == rhs.Numerator() && lhs.Denominator() == rhs.Denominator();
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
  return {lhs.Numerator() * rhs.Denominator() + rhs.Numerator() * lhs.Denominator(),
          lhs.Denominator() * rhs.Denominator()};
}

Rational operator-(const Rational& lhs, const Rational& rhs) {
  return {lhs.Numerator() * rhs.Denominator() - rhs.Numerator() * lhs.Denominator(),
          lhs.Denominator() * rhs.Denominator()};
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
  return {lhs.Numerator() * rhs.Numerator(), lhs.Denominator() * rhs.Denominator()};
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
  return {lhs.Numerator() * rhs.Denominator(), lhs.Denominator() * rhs.Numerator()};
}

std::ostream& operator<<(std::ostream& os, const Rational& rational) {
  os << rational.Numerator() << "/" << rational.Denominator();
  return os;
}

/// @remark bad implementation
std::istream& operator>>(std::istream& is, Rational& rational) {
  int numerator, denomirator;
  char delimiter;
  /// read numerator
  if (is) {
    is >> numerator;
  } else {
    return is;
  }
  /// read delimeter
  if (is && !is.fail()) {
    is >> delimiter;
  } else {
    return is;
  }
  /// check delimeter
  if (delimiter != '/') {
    return is;
  }
  /// read denomirator
  if (is && !is.fail()) {
    is >> denomirator;
  } else {
    return is;
  }
  if (is.fail()) {
    return is;
  }
  rational = Rational(numerator, denomirator);
  return is;
}

bool operator<(const Rational& lhs, const Rational& rhs) {
  return (lhs.Numerator() * rhs.Denominator()) < (rhs.Numerator() * lhs.Denominator());
}

int main() {
  {
    const std::set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
    if (rs.size() != 3) {
      std::cout << "Wrong amount of items in the set" << std::endl;
      return 1;
    }

    std::vector<Rational> v;
    for (auto x : rs) {
      v.push_back(x);
    }
    if (v != std::vector<Rational>{{1, 25}, {1, 2}, {3, 4}}) {
      std::cout << "Rationals comparison works incorrectly" << std::endl;
      return 2;
    }
  }

  {
    std::map<Rational, int> count;
    ++count[{1, 2}];
    ++count[{1, 2}];

    ++count[{2, 3}];

    if (count.size() != 2) {
      std::cout << "Wrong amount of items in the map" << std::endl;
      return 3;
    }
  }

  std::cout << "OK" << std::endl;
  return 0;
}
