#ifndef A_LINE_H
#define A_LINE_H

#include "IShape.h"
#include "point.h"
#include "vector.h"
#include <string>

namespace geometry {

class Line : public IShape {
 public:
  Line() : a_(0), b_(0), c_(0) {
  }

  Line(int x, int y, int z) : a_(x), b_(y), c_(z) {
  }

  Line(const Point &p, const Vector &v);

  Line(const Point &p1, const Point &p2);

  Line(const Line &other) : a_(other.a_), b_(other.b_), c_(other.c_) {
  }

  Line operator=(const Line &other);

 public:
  Line &Move(const Vector &v) override;
  bool ContainsPoint(const Point &p) const override;
  bool CrossesSegment(const Segment &) const override;
  Line *Clone() const override;
  std::string ToString() const override;

 public:
  bool operator==(const Line &other) const {
    return this == &other || (a_ == other.a_ && b_ == other.b_ && c_ == other.c_);
  }
  bool operator!=(const Line &other) const {
    return !(*this == other);
  }

 public:
  int GetA() const {
    return a_;
  }
  int GetB() const {
    return b_;
  }
  int GetC() const {
    return c_;
  }
  Point GetP() const;
  Vector GetN() const;
  Vector GetV() const;

  bool GetPointY(Point &p) const;
  bool GetPoint(Point &p) const;

  bool PointPlane(const Point &p1, const Point &p2) const;
  bool IsParralel(const Line &other) const;

  double Distance(const Point &p) const;

 private:
  void Swap(Line &p1, Line &p2) {
    std::swap(p1.a_, p2.a_);
    std::swap(p1.b_, p2.b_);
    std::swap(p1.c_, p2.c_);
  }

 private:
  int a_;
  int b_;
  int c_;
};

}  // namespace geometry

#endif