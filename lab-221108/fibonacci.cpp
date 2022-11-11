#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

int fibonacci(int N) {
  if (N <= 0) {
    return -1;
  }

  int previous{};
  int current{1};

  for (int n{1}; n < N; n++) {
    int t{current};
    current = previous + current;
    previous = t;
  }

  return current;
}

TEST_CASE("Testing Fibonacci") {
  CHECK(fibonacci(1) == 1);
  CHECK(fibonacci(2) == 1);
  CHECK(fibonacci(3) == 2);
  CHECK(fibonacci(4) == 3);
  CHECK(fibonacci(5) == 5);
  CHECK(fibonacci(6) == 8);
}