#include <iostream>

int main() {
  char b;
  int c = 0;
  int p = 0;
  while (std::cin >> b) {
    if (b == '(') {
      c++;
    } else if (b == ')') {
      if (c <= 0) {
        p++;
      } else {
        c--;
      }
    } else {
      break;
    }
  }
  std::cout << std::abs(c) + p;
  return 0;
}
