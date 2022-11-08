#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <cmath>

#include "doctest.h"

int factorial(int n) {
  if (n < 0) {
    return -1;
  }

  if (n == 0 || n == 1) {
    return 1;
  }

  return factorial(n - 1) * n;
}

double taylor(double x, int N) {
  if (N < 0) {
    return -1;
  }

  double sum{};

  for (int n{}; n <= N; ++n) {
    sum += (std::pow(-1, n) / factorial(2 * n)) * std::pow(x, 2 * n);
  };

  return sum;
}

TEST_CASE("Testing the factorial function") {
  CHECK(factorial(5) == 120);
  CHECK(factorial(-12) == -1);
  CHECK(factorial(10) == 3628800);
  CHECK(factorial(3) == 6);
}

TEST_CASE("Testing the Taylor expansion") {
  CHECK(taylor(0.5, 1) == doctest::Approx(0.875));
  CHECK(taylor(0.5, 2) == doctest::Approx(0.877).epsilon(0.001));
  CHECK(taylor(0.5, 3) == doctest::Approx(0.877).epsilon(0.001));
  CHECK(taylor(0.5, -9) == -1);
}