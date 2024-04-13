#include <iostream>
#include <cmath>

int main() {
  int n1, n2;
  std::cin >> n1 >> n2;
  int a = n1, b = n2;
  int k = (a * b) / std::abs(a * b);
  if (a < 0) {
    a = -a;
  }
  if (b < 0) {
    b = -b;
  }
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
  std::cout << k * std::abs(n1 / b) << " " << std::abs(n2 / b);
  return 0;
}
