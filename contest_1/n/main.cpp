#include <iostream>
#include <cmath>

int main() {
  int a, b;
  std::cin >> a >> b;
  int c = 0;
  int tmp = a;
  a = std::max(a, b);
  b = std::min(tmp, b);
  while (a % b != 0) {
    c += a / b;
    a = a % b;
    int tmp = a;
    a = std::max(a, b);
    b = std::min(tmp, b);
  }
  c += a / b;
  std::cout << c;
  return 0;
}
