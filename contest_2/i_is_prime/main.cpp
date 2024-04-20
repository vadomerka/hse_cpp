#include <iostream>

int main() {
  int n, d = 2;
  std::cin >> n;
  while (d * d <= n) {
    if (n % d == 0) {
      std::cout << "composite";
      return 0;
    }
    d++;
  }
  std::cout << "prime";
  return 0;
}
