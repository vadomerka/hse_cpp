#include <cmath>
#include <iostream>

int main() {
  int n1, n2;
  std::cin >> n1 >> n2;
  if (n1 == 0) {
    std::cout << "0 1";
    return 0;
  }
  if (n2 == 0) {
    std::cout << n1 << " " << n2;
    return 0;
  }
  int a = n1, b = n2;
  int sign = (a * b) / std::abs(a * b);
  a = std::abs(a);
  b = std::abs(b);
  if (a < b) {
    std::swap(a, b);
  }
  while (a % b != 0) {
    int tmp = a;
    a = b;
    b = tmp % b;
    if (a < b) {
      std::swap(a, b);
    }
  }
  std::cout << sign * std::abs(n1 / b) << " " << std::abs(n2 / b);
  return 0;
}
