#ifndef A_LINE_H
#define A_LINE_H

#include "IShape.h"
#include <string>

namespace geometry {

class Line : IShape {
public:
  Line()
   : a_(0)
   , b_(0)
   , c_(0)
  {}

  Line(int x, int y, int z)
  : a_(x)
  , b_(y)
  , c_(z)
  {}

  Line(const Line& other)
  : a_(other.a_)
  , b_(other.b_)
  , c_(other.c_)
  {}

  ~Line() = default;

  Line operator=(const Line& other);

public:
  void Move(const Vector& v) override;
  bool ContainsPoint(const Point& p) override;
  bool CrossesSegment(const Segment &) override;
  Line* Clone() override;
  std::string ToString() override;

public:
  bool operator==(const Line& other) const {
    return this == &other || a_ == other.a_ && b_ == other.b_ && c_ == other.c_;
  }
  bool operator!=(const Line& other) const {
    return !(*this == other);
  }

public:
  int GetA() const { return a_; }
  int GetB() const { return b_; }
  int GetC() const { return c_; }
  Vector GetN() const;
  Vector GetV() const;

  bool PointPlane(const Point& p1, const Point& p2) const;
  bool IsParralel(const Line& other) const;

private:
  void Swap(Line& p1, Line& p2) {
    std::swap(p1.a_, p2.a_);
    std::swap(p1.b_, p2.b_);
    std::swap(p1.c_, p2.c_);
  }

private:
  int a_;
  int b_;
  int c_;
};

} // namespace geometry

#endif