#include <ios>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
 
int MAX_NUM = 2000000000;
 
struct Point {
  int x = 0;
  int y = 0;
 
  Point() {}
 
  Point(int xx, int yy) : x(xx), y(yy) {}
 
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
 
  int dist(const Point &other) const {
    return std::sqrt((std::abs(x - other.x) * std::abs(x - other.x) +
                      std::abs(y - other.y) * std::abs(y - other.y)));
  }
};
 
int naiive(const std::vector<Point> &points) {
  int mdist = std::sqrt(2 * 1000000000 * 1000000000);
  for (size_t i = 0; i < points.size() - 1; i++) {
    for (size_t j = i + 1; j < points.size(); j++) {
      int nd = points[i].dist(points[j]);
      if (nd < mdist) {
        mdist = nd;
      }
    }
  }
  return mdist;
}
 
struct sort_x_y {
  bool operator()(const Point& p1, const Point& p2) { 
    if (p1.x == p2.x) {
      return p1.y < p2.y;
    }
    return p1.x < p2.x; 
  }
};
 
struct sort_y {
  bool operator()(const Point& p1, const Point& p2) { 
    return p1.y < p2.y;
  }
};
 
int closestPair(std::vector<Point> &p, int start, int end) {
  size_t len = end - start;
  if (len == 2) {
    return p[start].dist(p[start + 1]);
  }
  if (len == 3) {
    return std::min(std::min(p[start].dist(p[start + 1]), 
                             p[start + 1].dist(p[start + 2])), 
                             p[start].dist(p[start + 2]));
  }
  
  int l = (p[end - 1].x - p[start].x) / 2;
  int lind = 0;
  for (int i = start; i < end; i++) {
    if (p[i].x >= l) {
      lind = i;
      break;
    }
  }
  int d = std::min(closestPair(p, start, lind), closestPair(p, lind, end));
  std::vector<Point> ps1;
  for (size_t i = start; i < end; i++) {
    int ldist = std::abs(p[i].x - l);
    if (ldist <= d) {
      ps1.push_back(p[i]);
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
 
  int n = 0;
  std::vector<int> input;
  std::vector<Point> pns;
 
  while (std::cin >> n) {
    input.push_back(n);
  }
  for (size_t i = 0; i < input.size(); i += 2) {
    pns.push_back({input[i], input[i + 1]});
  }
 
  // std::cout << naiive(pns);
  std::sort(pns.begin(), pns.end(), sort_x_y());
  std::cout << closestPair(pns, 0, pns.size());
  return 0;
}