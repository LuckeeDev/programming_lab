#include <iostream>

int main() {
  int first;
  int second;

  std::cout << "First number: ";
  std::cin >> first;

  std::cout << "Second number: ";
  std::cin >> second;

  int result{first + second};

  std::cout << "The sum is: " << result << '\n';
}