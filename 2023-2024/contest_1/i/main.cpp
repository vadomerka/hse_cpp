#include <iostream>

int main() {
  int a;
  std::cin >> a;
  for (int i = 2; i <= a; i += 1) {
    if (a % i == 0) {
      std::cout << i;
      return 0;
    }
  }
  return 0;
}
