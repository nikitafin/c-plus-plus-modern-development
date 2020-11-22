#include <iostream>
#include <numeric>

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

int main() {
  {
    const Rational r(3, 10);
    if (r.Numerator() != 3 || r.Denominator() != 10) {
      std::cout << "Rational(3, 10) != 3/10" << std::endl;
      return 1;
    }
  }

  {
    const Rational r(8, 12);
    if (r.Numerator() != 2 || r.Denominator() != 3) {
      std::cout << "Rational(8, 12) != 2/3" << std::endl;
      return 2;
    }
  }

  {
    const Rational r(-4, 6);
    if (r.Numerator() != -2 || r.Denominator() != 3) {
      std::cout << "Rational(-4, 6) != -2/3" << std::endl;
      return 3;
    }
  }

  {
    const Rational r(4, -6);
    if (r.Numerator() != -2 || r.Denominator() != 3) {
      std::cout << "Rational(4, -6) != -2/3" << std::endl;
      return 3;
    }
  }

  {
    const Rational r(0, 15);
    if (r.Numerator() != 0 || r.Denominator() != 1) {
      std::cout << "Rational(0, 15) != 0/1" << std::endl;
      return 4;
    }
  }

  {
    const Rational defaultConstructed;
    if (defaultConstructed.Numerator() != 0 || defaultConstructed.Denominator() != 1) {
      std::cout << "Rational() != 0/1" << std::endl;
      return 5;
    }
  }

  std::cout << "OK" << std::endl;
  return 0;
}
