#ifndef A_RAY_H
#define A_RAY_H

#include "IShape.h"
#include "point.h"
#include "vector.h"
#include <string>

namespace geometry {

class Ray : public IShape {
 public:
  Ray() : p_(), v_() {
  }

  Ray(const Point &p, const Vector &v) : p_(p), v_(v) {
  }

  Ray(const Point &p1, const Point &p2) : p_(p1), v_(p2 - p1) {
  }

  Ray(const Ray &other) : p_(other.p_), v_(other.v_) {
  }

  Ray operator=(const Ray &other);

 public:
  Ray &Move(const Vector &v) override;
  bool ContainsPoint(const Point &p) const override;
  bool CrossesSegment(const Segment &) const override;
  Ray *Clone() const override;
  std::string ToString() const override;

 public:
  bool operator==(const Ray &other) const {
    return this == &other || (p_ == other.p_ && Vector::AreCoDirected(v_, other.v_));
  }
  bool operator!=(const Ray &other) const {
    return !(*this == other);
  }

 public:
  Point GetPoint() const {
    return p_;
  }
  Vector GetVector() const {
    return v_;
  }
  Line GetLine() const;

  double Distance(const Point &p) const;
  bool IsParralel(const Ray &other) const;
  bool ContainsSegment(const Segment &) const;

 private:
  void Swap(Ray &p1, Ray &p2) {
    std::swap(p1.p_, p2.p_);
    std::swap(p1.v_, p2.v_);
  }

 private:
  Point p_;
  Vector v_;
};

}  // namespace geometry

#endif