#ifndef A_POINT_H
#define A_POINT_H

#include "IShape.h"
#include <string>

namespace geometry {

class Point : public IShape {
 public:
  Point() : x_(0), y_(0) {
  }

  Point(int x, int y) : x_(x), y_(y) {
  }

  Point(const Point &other) : x_(other.x_), y_(other.y_) {
  }

  Point operator=(const Point &other) {
    if (this == &other) {
      return *this;
    }
    Point tmp = other;
    Swap(*this, tmp);
    return *this;
  }

 public:
  Point &Move(const Vector &v) override;
  bool ContainsPoint(const Point &p) const override {
    return *this == p;
  }
  bool CrossesSegment(const Segment &segment) const override;
  Point *Clone() const override {
    return new Point(*this);
  }
  std::string ToString() const override {
    std::string vars[]{std::to_string(x_), std::to_string(y_)};
    return StringFormat("Point", vars, 2);
  }

 public:
  bool operator==(const Point &other) const {
    return this == &other || (x_ == other.x_ && y_ == other.y_);
  }
  bool operator!=(const Point &other) const {
    return !(*this == other);
  }

  Vector operator-(const Point &other) const;

 public:
  int &GetX() {
    return x_;
  }
  int &GetY() {
    return y_;
  }
  int GetX() const {
    return x_;
  }
  int GetY() const {
    return y_;
  }
  static double Distance(const Point &p1, const Point &p2);

 private:
  void Swap(Point &p1, Point &p2) {
    std::swap(p1.x_, p2.x_);
    std::swap(p1.y_, p2.y_);
  }

 private:
  int x_;
  int y_;
};

}  // namespace geometry

#endif