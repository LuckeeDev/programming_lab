#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <cmath>

#include "doctest.h"

int gcd(int a, int b) {
  if (b == 0) {
    return a;
  } else {
    return gcd(b, a % b);
  }
}

int lcm(int a, int b) { return std::abs(a * b) / gcd(a, b); }

TEST_CASE("Testing least common multiple") {
  CHECK(lcm(12, 16) == 48);
  CHECK(lcm(26, 15) == 390);
  CHECK(lcm(6, 6) == 6);
  CHECK(lcm(-12, 6) == 12);
  CHECK(lcm(0, 123123) == 0);
}
