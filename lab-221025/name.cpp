#include <iostream>

int main() {
  std::cout << "What's your name?\n";
  std::string name;
  std::cin >> name;
  std::cout << "Hi " << name << '!' << '\n';
}