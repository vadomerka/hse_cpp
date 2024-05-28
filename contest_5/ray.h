#ifndef A_RAY_H
#define A_RAY_H

#include "IShape.h"
#include "point.h"
#include "vector.h"
#include <string>

namespace geometry {

class Ray : IShape {
public:
  Ray()
   : p_()
   , v_()
  {}

  Ray(Point p, Vector v)
  : p_(p)
  , v_(v)
  {}

  Ray(const Ray& other)
  : p_(other.p_)
  , v_(other.v_)
  {}

  ~Ray() = default;

  Ray operator=(const Ray& other);

public:
  void Move(const Vector& v) override;
  bool ContainsPoint(const Point& p) override;
  bool CrossesSegment(const Segment &) override;
  Ray* Clone() override;
  std::string ToString() override;

public:
  bool operator==(const Ray& other) const {
    return this == &other;
  }
  bool operator!=(const Ray& other) const {
    return !(*this == other);
  }

public:
  Point GetPoint() const { return p_; }
  Vector GetVector() const { return v_; }

  double Distance(const Point& p) const;
  // bool PointPlane(const Point& p1, const Point& p2) const;
  bool IsParralel(const Ray& other) const;

private:
  void Swap(Ray& p1, Ray& p2) {
    std::swap(p1.p_, p2.p_);
    std::swap(p1.v_, p2.v_);
  }

private:
  Point p_;
  Vector v_;
};

} // namespace geometry

#endif