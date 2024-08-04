#include <gtest/gtest.h>

unsigned int Factorial(unsigned int number) {
  return number <= 1 ? number : Factorial(number - 1) * number;
}

TEST(Factorials, Smoke) {
  EXPECT_TRUE(Factorial(1) == 1);
  EXPECT_TRUE(Factorial(2) == 2);
  EXPECT_TRUE(Factorial(3) == 6);
  EXPECT_TRUE(Factorial(10) == 3628800);
}
