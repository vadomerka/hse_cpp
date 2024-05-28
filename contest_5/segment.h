#ifndef A_SEGMENT_H
#define A_SEGMENT_H

#include "IShape.h"
#include "point.h"
#include "vector.h"

namespace geometry {

class Segment : IShape {
public:
  Segment()
   : p1_()
   , p2_()
  {}

  Segment(int x1, int y1, int x2, int y2)
  : p1_(x1, y1)
  , p2_(x2, y2)
  {}

  Segment(const Point& p1, const Point& p2)
  : p1_(p1)
  , p2_(p2)
  {}

  Segment(const Segment& other)
  : p1_(other.p1_)
  , p2_(other.p2_)
  {}

  ~Segment() = default;

  Segment operator=(const Segment& other){
    if (this == &other) { return *this; }
    Segment tmp = other;
    Swap(*this, tmp);
    return *this;
  }

public:
  void Move(const Vector& v) override;
  bool ContainsPoint(const Point& p) override {
    Vector v1 (p1_, p);
    Vector v2 (p, p2_);
    return Vector::IsColliniar(v1, v2);
  }
  bool CrossesSegment(const Segment &) override {
    return true;
  }
  Segment* Clone() override {
    return new Segment(*this);
  }
  std::string ToString() override {
    std::string vars[] { p1_.ToString(), p2_.ToString() };
    return StringFormat("Segment", vars, 2);
  }

public:
  bool operator==(const Segment& other) const {
    return this == &other || p1_ == other.p1_ && p2_ == other.p2_;
  }
  bool operator!=(const Segment& other) const {
    return !(*this == other);
  }

public:
  Point GetPoint1() const {
    return p1_;
  }
  Point GetPoint2() const {
    return p2_;
  }

private:
  void Swap(Segment& p1, Segment& p2) {
    std::swap(p1.p1_, p2.p1_);
    std::swap(p1.p2_, p2.p2_);
  }

private:
  Point p1_;
  Point p2_;
};

} // namespace geometry
#endif