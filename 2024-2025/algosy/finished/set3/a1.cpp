#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <fstream>


struct Point {
  Point(double x, double y) : _x(x), _y(y) {}

  double _x = 0;
  double _y = 0;
};

double dist(const Point& p1, const Point& p2) {
  return std::sqrt((p1._x - p2._x) * (p1._x - p2._x) + (p1._y - p2._y) * (p1._y - p2._y));
}

bool IsInCirc(const Point& p1, double r, const Point& center) {
  return dist(p1, center) <= r;
}


double Mont(int n, Point c1, double r1, Point c2, double r2, Point c3, double r3) {
  std::random_device dev;
  std::mt19937 rng(dev());
  double left = std::max(std::max(c1._x - r1, c2._x - r2), c3._x - r3);
  double right = std::min(std::min(c1._x + r1, c2._x + r2), c3._x + r3);
  double top = std::min(std::min(c1._y + r1, c2._y + r2), c3._y + r3);
  double bottom = std::max(std::max(c1._y - r1, c2._y - r2), c3._y - r3);
  std::uniform_real_distribution<double> unifx(left, right);
  std::uniform_real_distribution<double> unify(bottom, top);

  double countIn = 0;
  for (int i = 0; i < n; i++) {
    Point np{unifx(rng), unify(rng)};
    if (IsInCirc(np, r1, c1) &&
        IsInCirc(np, r2, c2) &&
        IsInCirc(np, r3, c3)) {
      countIn++;
    }
  }
  return (countIn / n) * (right - left) * (top - bottom);
}


int main() {
  double x = 0;
  double y = 0;
  double r = 0;
  std::cin >> x >> y >> r;
  Point c1 {x, y};
  double r1 = r;
  std::cin >> x >> y >> r;
  Point c2 {x, y};
  double r2 = r;
  std::cin >> x >> y >> r;
  Point c3 {x, y};
  double r3 = r;

  std::cout << Mont(200000, c1, r1, c2, r2, c3, r3) << '\n';
  return 0;
}