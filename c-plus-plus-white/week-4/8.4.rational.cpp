#include <iostream>
#include <numeric>
#include <sstream>

class Rational {
public:
  Rational() : numerator(0), denominator(1) {}
  Rational(int newNumerator, int newDenominator) {
    if (newNumerator == 0) {
      numerator   = 0;
      denominator = 1;
    } else {
      int sign  = ((newNumerator > 0 && newDenominator > 0) ||
                  (newNumerator < 0 && newDenominator < 0))
                      ? 1
                      : -1;
      int gcd   = std::gcd(newNumerator, newDenominator);
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

bool
operator==(const Rational &lhs, const Rational &rhs) {
  return lhs.Numerator() == rhs.Numerator() &&
         lhs.Denominator() == rhs.Denominator();
}

Rational
operator+(const Rational &lhs, const Rational &rhs) {
  return {lhs.Numerator() * rhs.Denominator() +
              rhs.Numerator() * lhs.Denominator(),
          lhs.Denominator() * rhs.Denominator()};
}

Rational
operator-(const Rational &lhs, const Rational &rhs) {
  return {lhs.Numerator() * rhs.Denominator() -
              rhs.Numerator() * lhs.Denominator(),
          lhs.Denominator() * rhs.Denominator()};
}

Rational
operator*(const Rational &lhs, const Rational &rhs) {
  return {lhs.Numerator() * rhs.Numerator(),
          lhs.Denominator() * rhs.Denominator()};
}

Rational
operator/(const Rational &lhs, const Rational &rhs) {
  return {lhs.Numerator() * rhs.Denominator(),
          lhs.Denominator() * rhs.Numerator()};
}

std::ostream &
operator<<(std::ostream &os, const Rational &rational) {
  os << rational.Numerator() << "/" << rational.Denominator();
  return os;
}

std::istream &
operator>>(std::istream &is, Rational &rational) {
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

int
main() {
  {
    std::ostringstream output;
    output << Rational(-6, 8);
    if (output.str() != "-3/4") {
      std::cout << "Rational(-6, 8) should be written as \"-3/4\"" << std::endl;
      return 1;
    }
  }

  {
    std::istringstream input("5/7");
    Rational r;
    input >> r;
    bool equal = r == Rational(5, 7);
    if (!equal) {
      std::cout << "5/7 is incorrectly read as " << r << std::endl;
      return 2;
    }
  }

  {
    std::istringstream input("");
    Rational r;
    bool correct = !(input >> r);
    if (!correct) {
      std::cout << "Read from empty stream works incorrectly" << std::endl;
      return 3;
    }
  }

  {
    std::istringstream input("5/7 10/8");
    Rational r1, r2;
    input >> r1 >> r2;
    bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
    if (!correct) {
      std::cout << "Multiple values are read incorrectly: " << r1 << " " << r2
                << std::endl;
      return 4;
    }

    input >> r1;
    input >> r2;
    correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
    if (!correct) {
      std::cout << "Read from empty stream shouldn't change arguments: " << r1
                << " " << r2 << std::endl;
      return 5;
    }
  }

  {
    std::istringstream input1("1*2"), input2("1/"), input3("/4");
    Rational r1, r2, r3;
    input1 >> r1;
    input2 >> r2;
    input3 >> r3;
    bool correct = r1 == Rational() && r2 == Rational() && r3 == Rational();
    if (!correct) {
      std::cout
          << "Reading of incorrectly formatted rationals shouldn't change "
             "arguments: "
          << r1 << " " << r2 << " " << r3 << std::endl;

      return 6;
    }
  }

  std::cout << "OK" << std::endl;
  return 0;
}
