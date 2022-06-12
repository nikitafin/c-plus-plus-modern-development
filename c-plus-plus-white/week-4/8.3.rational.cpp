#include <iostream>
#include <numeric>

class Rational
{
public:
    Rational() : numerator(0), denominator(1)
    {
    }
    Rational(int newNumerator, int newDenominator)
    {
        if (newNumerator == 0)
        {
            numerator = 0;
            denominator = 1;
        }
        else
        {
            int sign = ((newNumerator > 0 && newDenominator > 0)
                        || (newNumerator < 0 && newDenominator < 0))
                ? 1
                : -1;
            int gcd = std::gcd(newNumerator, newDenominator);
            numerator = std::abs(newNumerator / gcd);
            numerator *= sign;
            denominator = std::abs(newDenominator / gcd);
        }
    }

    int Numerator() const
    {
        return numerator;
    }
    int Denominator() const
    {
        return denominator;
    }

private:
    int numerator;
    int denominator;
};

bool operator==(const Rational & lhs, const Rational & rhs)
{
    return lhs.Numerator() == rhs.Numerator() && lhs.Denominator() == rhs.Denominator();
}

Rational operator+(const Rational & lhs, const Rational & rhs)
{
    return {
        lhs.Numerator() * rhs.Denominator() + rhs.Numerator() * lhs.Denominator(),
        lhs.Denominator() * rhs.Denominator()};
}

Rational operator-(const Rational & lhs, const Rational & rhs)
{
    return {
        lhs.Numerator() * rhs.Denominator() - rhs.Numerator() * lhs.Denominator(),
        lhs.Denominator() * rhs.Denominator()};
}

Rational operator*(const Rational & lhs, const Rational & rhs)
{
    return {lhs.Numerator() * rhs.Numerator(), lhs.Denominator() * rhs.Denominator()};
}

Rational operator/(const Rational & lhs, const Rational & rhs)
{
    return {lhs.Numerator() * rhs.Denominator(), lhs.Denominator() * rhs.Numerator()};
}

int main()
{
    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a * b;
        bool equal = c == Rational(8, 9);
        if (!equal)
        {
            std::cout << "2/3 * 4/3 != 8/9" << std::endl;
            return 1;
        }
    }

    {
        Rational a(5, 4);
        Rational b(15, 8);
        Rational c = a / b;
        bool equal = c == Rational(2, 3);
        if (!equal)
        {
            std::cout << "5/4 / 15/8 != 2/3" << std::endl;
            return 2;
        }
    }

    std::cout << "OK" << std::endl;
    return 0;
}