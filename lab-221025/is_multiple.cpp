#include <iostream>

int main() {
  int first;
  int second;

  std::cout << "First number: ";
  std::cin >> first;

  std::cout << "Second number: ";
  std::cin >> second;

  int remainder{first % second};

  std::string is_multiple;

  if (remainder == 0) {
    is_multiple = " è multiplo di ";
  } else {
    is_multiple = " non è multiplo di ";
  }

  std::cout << first << is_multiple << second << '\n';
}