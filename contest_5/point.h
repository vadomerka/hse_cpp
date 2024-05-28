#ifndef A_POINT_H
#define A_POINT_H

#include "IShape.h"
#include <string>

namespace geometry {

class Point : IShape {
public:
  Point()
   : x_(0)
   , y_(0)
  {}

  Point(int x, int y)
  : x_(x)
  , y_(y)
  {}

  Point(const Point& other)
  : x_(other.x_)
  , y_(other.y_)
  {}

  ~Point() = default;

  Point operator=(const Point& other){
    if (this == &other) { return *this; }
    Point tmp = other;
    Swap(*this, tmp);
    return *this;
  }

public:
  void Move(const Vector& v) override;
  bool ContainsPoint(const Point& p) override { 
    return *this == p;
  }
  bool CrossesSegment(const Segment& segment) override;
  Point* Clone() override {
    return new Point(*this);
  }
  std::string ToString() override {
    std::string vars[] { std::to_string(x_), std::to_string(y_) };
    return StringFormat("Point", vars, 2);
  }

public:
  bool operator==(const Point& other) const {
    return this == &other || x_ == other.x_ && y_ == other.y_;
  }
  bool operator!=(const Point& other) const {
    return !(*this == other);
  }

public:
  int GetX() const {
    return x_;
  }
  int GetY() const {
    return y_;
  }

private:
  void Swap(Point& p1, Point& p2) {
    std::swap(p1.x_, p2.x_);
    std::swap(p1.y_, p2.y_);
  }

private:
  int x_;
  int y_;
};

} // namespace geometry

#endif