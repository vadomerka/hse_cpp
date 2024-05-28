#ifndef A_SEGMENT_H
#define A_SEGMENT_H

#include "IShape.h"
#include "point.h"
#include "vector.h"

namespace geometry {

class Segment : IShape {
public:
  Segment() : p1_(), p2_() {}

  Segment(int x1, int y1, int x2, int y2) : p1_(x1, y1), p2_(x2, y2) {}

  Segment(const Point &p1, const Point &p2) : p1_(p1), p2_(p2) {}

  Segment(const Segment &other) : p1_(other.p1_), p2_(other.p2_) {}

  ~Segment() = default;

  Segment operator=(const Segment &other);

public:
  void Move(const Vector &v) override;
  bool ContainsPoint(const Point &p) const override;
  bool CrossesSegment(const Segment &) const override;
  Segment *Clone() const override;
  std::string ToString() const override;

public:
  bool operator==(const Segment &other) const {
    return this == &other || p1_ == other.p1_ && p2_ == other.p2_;
  }
  bool operator!=(const Segment &other) const { return !(*this == other); }

public:
  Point GetPoint1() const { return p1_; }
  Point GetPoint2() const { return p2_; }
  Line GetLine() const;
  double GetLength() const { return Point::Distance(p1_, p2_); }
  double Distance(const Point &p);

  bool CrossesLine(const Line &l) const;

private:
  void Swap(Segment &p1, Segment &p2) {
    std::swap(p1.p1_, p2.p1_);
    std::swap(p1.p2_, p2.p2_);
  }

private:
  Point p1_;
  Point p2_;
};

} // namespace geometry
#endif