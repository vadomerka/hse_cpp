#ifndef A_CIRCLE_H
#define A_CIRCLE_H

#include "IShape.h"
#include "point.h"
#include "vector.h"

namespace geometry {

class Circle : public IShape {
 public:
  Circle() : center_(), radius_(0) {
  }

  Circle(const Point &point, size_t size) : center_(point), radius_(size) {
  }

  Circle(const Circle &other) : center_(other.center_), radius_(other.radius_) {
  }

  Circle operator=(const Circle &other);

 public:
  Circle &Move(const Vector &v) override;
  bool ContainsPoint(const Point &p) const override;
  bool CrossesSegment(const Segment &) const override;
  Circle *Clone() const override;
  std::string ToString() const override;

 public:
  bool operator==(const Circle &other) const;
  bool operator!=(const Circle &other) const {
    return !(*this == other);
  }

 private:
  void Swap(Circle &p1, Circle &p2) {
    std::swap(p1.center_, p2.center_);
    std::swap(p1.radius_, p2.radius_);
  }

 private:
  Point center_;
  size_t radius_;
};

}  // namespace geometry
#endif