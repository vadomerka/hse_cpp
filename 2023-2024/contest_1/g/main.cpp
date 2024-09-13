#include <iostream>

int main() {
  double a, b, c, d;
  std::cin >> a >> b >> c >> d;
  if (a == 0 && b == 0) {
    std::cout << "INF";
    return 0;
  }
  double x = -1 * b / a;
  double y = -1 * d / c;
  int intx = -1 * b / a;
  if (x == y) {
    std::cout << "NO";
  } else if (x == intx) {
    std::cout << intx;
  } else {
    std::cout << "NO";
  }
  return 0;
}
