#include <iostream>
#include <cmath>

int main() {
  int a;
  int b;
  std::cin >> a >> b;
  double res = sqrt(a * a + b * b);
  std::cout << res;
  return 0;
}
