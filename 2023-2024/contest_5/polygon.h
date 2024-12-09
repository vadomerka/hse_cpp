#ifndef A_POLYGON_H
#define A_POLYGON_H

#include "IShape.h"
#include "point.h"
#include "vector.h"
#include <vector>

namespace geometry {

class Polygon : public IShape {

 public:
  Polygon() : vertices_(), size_(0) {
  }

  Polygon(Point *points, size_t size) : vertices_(points), size_(size) {
  }

  explicit Polygon(std::vector<Point> point);

  Polygon(const Polygon &other);

  ~Polygon() override;

  Polygon operator=(const Polygon &other);

 public:
  Polygon &Move(const Vector &v) override;
  bool ContainsPoint(const Point &p) const override;
  bool CrossesSegment(const Segment &) const override;
  Polygon *Clone() const override;
  std::string ToString() const override;

 public:
  bool operator==(const Polygon &other) const;
  bool operator!=(const Polygon &other) const {
    return !(*this == other);
  }

 private:
  void Swap(Polygon &p1, Polygon &p2) {
    std::swap(p1.vertices_, p2.vertices_);
    std::swap(p1.size_, p2.size_);
  }
  bool HasIntersects(const Ray &r, const Segment &s, size_t idx) const;

 private:
  Point *vertices_;
  size_t size_;
};

}  // namespace geometry
#endif