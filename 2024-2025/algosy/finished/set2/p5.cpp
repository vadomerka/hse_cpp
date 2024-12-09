#include <algorithm>
#include <cmath>
#include <ios>
#include <iostream>
#include <vector>

struct Point {
  int x = 0;
  int y = 0;

  Point() {}

  Point(int xx, int yy) : x(xx), y(yy) {}

  long long dist(const Point &other) const {
    return 1LL * (x - other.x) * (x - other.x) + 1LL * (y - other.y) * (y - other.y);
  }
};

bool sort_x(const Point &p1, const Point &p2) { return p1.x < p2.x; }

bool sort_y(const Point &p1, const Point &p2) { return p1.y < p2.y; }

long long closestPair(std::vector<Point> &p, int start, int end) {
  if (end - start <= 3) {
    long long md = std::numeric_limits<long long>::max();
    for (int i = start; i < end; i++) {
      for (int j = i + 1; j < end; j++) {
        md = std::min(md, p[i].dist(p[j]));
      }
    }
    return md;
  }

  int lind = start + (end - start) / 2;
  Point lp = p[lind];
  long long d = std::min(closestPair(p, start, lind), closestPair(p, lind, end));
  std::vector<Point> ps1;
  for (int i = start; i < end; i++) {
    long long ldist = 1LL * (p[i].x - lp.x) * (p[i].x - lp.x);
    if (ldist < d) {
      ps1.push_back(p[i]);
    }
  }
  std::sort(ps1.begin(), ps1.end(), sort_y);
  for (size_t i = 0; i < ps1.size(); i++) {
    for (size_t j = i + 1; j < ps1.size(); j++) {
      // (strip[j].y - strip[i].y) * (strip[j].y - strip[i].y) < minDist
      if ((ps1[j].y - ps1[i].y) * 
          (ps1[j].y - ps1[i].y) >= d) {
        break;
      }
      d = std::min(d, ps1[i].dist(ps1[j]));
    }
  }
  return d;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int x = 0, y = 0;
  std::vector<Point> pns;
  while (std::cin >> x >> y) {
    pns.emplace_back(x, y);
  }

  if (pns.size() <= 1) {
    std::cout << "0\n";
    return 0;
  }

  // std::cout << naiive(pns);
  std::sort(pns.begin(), pns.end(), sort_x);
  std::cout << (long long)std::sqrt(closestPair(pns, 0, pns.size()));
  return 0;
}