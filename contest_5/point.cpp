#include "point.h"
#include "vector.h"
#include "segment.h"

namespace geometry
{
  
void Point::Move(const Vector& v) {
  x_ += v.GetA();
  y_ += v.GetB();
}

bool Point::CrossesSegment(const Segment& segment) const {
  Vector v1 (segment.GetPoint1(), *this);
  Vector v2 (*this, segment.GetPoint2());
  return Vector::AreColliniar(v1, v2);
}

double Point::Distance(const Point& p1, const Point& p2) {
  Vector v(p1, p2);
  return v.GetLength();
}

} // namespace geometry