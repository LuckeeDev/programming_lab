#include <iostream>

int sum_all_naturals(int n) { return n * (n + 1) / 2; };

int main() {
  int from;
  int to;

  std::cout << "Sum all natural numbers from: ";
  std::cin >> from;

  std::cout << "Up until: ";
  std::cin >> to;

  int result{sum_all_naturals(to) - sum_all_naturals(from) + from};

  std::cout << "Result: " << result << '\n';
}