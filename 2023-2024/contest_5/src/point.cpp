#include "../point.h"
#include "../vector.h"
#include "../segment.h"

namespace geometry {

Point& Point::Move(const Vector& v) {
  x_ += v.GetA();
  y_ += v.GetB();
  return *this;
}

bool Point::CrossesSegment(const Segment& segment) const {
  return segment.ContainsPoint(*this);
}

double Point::Distance(const Point& p1, const Point& p2) {
  Vector v(p1, p2);
  return v.GetLength();
}

Vector Point::operator-(const Point& other) const {
  return Vector(other, *this);
}

}  // namespace geometry