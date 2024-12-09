#include <ios>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

int64_t MAX_NUM = std::sqrt(2 * 1000000000 * 1000000000);

struct Point {
  int64_t x = 0;
  int64_t y = 0;

  Point() {}

  Point(int64_t xx, int64_t yy) : x(xx), y(yy) {}

  Point(const Point& other) : x(other.x), y(other.y) {}

  Point(const Point&& other) : x(other.x), y(other.y) {}

  Point operator=(const Point& other) {
    x = other.x;
    y = other.y;
    return *this;
  }

  Point operator=(const Point&& other) {
    x = other.x;
    y = other.y;
    return *this;
  }

  int64_t dist(const Point &other) const {
    return std::sqrt((std::abs(x - other.x) * std::abs(x - other.x) +
                      std::abs(y - other.y) * std::abs(y - other.y)));
  }
};

int64_t naiive(const std::vector<Point> &points) {
  int64_t mdist = std::sqrt(2 * 1000000000 * 1000000000);
  for (size_t i = 0; i < points.size() - 1; i++) {
    for (size_t j = i + 1; j < points.size(); j++) {
      int64_t nd = points[i].dist(points[j]);
      if (nd < mdist) {
        mdist = nd;
      }
    }
  }
  return mdist;
}

struct sort_x_y {
  bool operator()(Point p1, Point p2) { 
    if (p1.x == p2.x) {
      return p1.y < p2.y;
    }
    return p1.x < p2.x; 
  }
};

struct sort_y {
  bool operator()(Point p1, Point p2) { 
    return p1.y < p2.y;
  }
};

int64_t closestPair(std::vector<Point> &p) {
  if (p.size() == 2) {
    return p[0].dist(p[1]);
  }
  if (p.size() == 3) {
    return std::min(std::min(p[0].dist(p[1]), p[1].dist(p[2])), p[0].dist(p[2]));
  }
  std::sort(p.begin(), p.end(), sort_x_y());
  int64_t l = (p[p.size() - 1].x - p[0].x) / 2;
  std::vector<Point> p1;
  std::vector<Point> p2;
  for (size_t i = 0; i < p.size(); i++) {
    if (p[i].x < l) {
      p1.push_back(p[i]);
    } else {
      p2.push_back(p[i]);
    }
  }
  int64_t d = std::min(closestPair(p1), closestPair(p2));
  std::vector<Point> ps1;
  for (size_t i = 0; i < p1.size(); i++) {
    int64_t ldist = std::abs(p1[i].x - l);
    if (ldist <= d) {
      ps1.push_back(p1[i]);
    }
  }
  for (size_t i = 0; i < p2.size(); i++) {
    int64_t ldist = std::abs(p2[i].x - l);
    if (ldist <= d) {
      ps1.push_back(p2[i]);
    }
  }
  std::sort(ps1.begin(), ps1.end(), sort_y());
  for (size_t i = 0; i < ps1.size() - 1; i++) {
    d = std::min(ps1[i].dist(ps1[i + 1]), d);
    d = (i + 2 < ps1.size()) ? std::min(ps1[i].dist(ps1[i + 2]), d) : d;
    d = (i + 3 < ps1.size()) ? std::min(ps1[i].dist(ps1[i + 3]), d) : d;
    d = (i + 4 < ps1.size()) ? std::min(ps1[i].dist(ps1[i + 4]), d) : d;
    d = (i + 5 < ps1.size()) ? std::min(ps1[i].dist(ps1[i + 5]), d) : d;
    d = (i + 6 < ps1.size()) ? std::min(ps1[i].dist(ps1[i + 6]), d) : d;
  }
  return d;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int64_t n = 0;
  std::vector<int64_t> input;
  std::vector<Point> pns;

  while (std::cin >> n) {
    input.push_back(n);
  }
  for (size_t i = 0; i < input.size(); i += 2) {
    pns.push_back({input[i], input[i + 1]});
  }

  // std::cout << naiive(pns);
  std::cout << closestPair(pns);
  return 0;
}
