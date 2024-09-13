#include <iostream>

bool IsDigit(unsigned char c) {
  return ('0' <= c && c <= '9');
}

int main() {
  char ch;
  std::cin >> ch;
  if (IsDigit(ch)) {
    std::cout << "yes";
  } else {
    std::cout << "no";
  }
  return 0;
}
