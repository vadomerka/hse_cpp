#include <cmath>
#include <iomanip>
#include <iostream>

double LineLength(double x1, double y1, double x2, double y2) {
  return sqrt((y2 - y1) * (y2 - y1) + (x2 - x1) * (x2 - x1));
}

int main() {
  double x1, y1, x2, y2, x3, y3;
  std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
  double res = LineLength(x1, y1, x2, y2) + LineLength(x3, y3, x2, y2) + LineLength(x1, y1, x3, y3);
  std::cout << std::setprecision(7) << res;
  return 0;
}
