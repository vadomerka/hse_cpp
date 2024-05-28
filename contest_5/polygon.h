#ifndef A_POLYGON_H
#define A_POLYGON_H

#include "IShape.h"
#include "point.h"
#include "vector.h"

namespace geometry {

class Polygon : IShape {
public:
  Polygon() : vertices_(), size_(0) {}

  Polygon(Point* points, size_t size) : vertices_(points), size_(size) {}

  Polygon(const Polygon &other) : vertices_(other.vertices_), size_(other.size_) {}

  ~Polygon() = default;

  Polygon operator=(const Polygon &other);

public:
  void Move(const Vector &v) override;
  bool ContainsPoint(const Point &p) const override;
  bool CrossesSegment(const Segment &) const override;
  Polygon *Clone() const override;
  std::string ToString() const override;

public:
  bool operator==(const Polygon &other) const {
    return this == &other;
  }
  bool operator!=(const Polygon &other) const { return !(*this == other); }

public:

private:
  void Swap(Polygon &p1, Polygon &p2) {
    std::swap(p1.vertices_, p2.vertices_);
    std::swap(p1.size_, p2.size_);
  }

private:
  Point* vertices_;
  size_t size_;
};

} // namespace geometry
#endif