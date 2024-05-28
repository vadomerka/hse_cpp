#include "point.h"
#include "vector.h"
#include "segment.h"

namespace geometry
{
  
void Point::Move(const Vector& v) {
  x_ += v.GetA();
  y_ += v.GetB();
}

bool Point::CrossesSegment(const Segment& segment) {
  Vector v1 (segment.GetPoint1(), *this);
  Vector v2 (*this, segment.GetPoint2());
  return Vector::IsColliniar(v1, v2);
}

} // namespace geometry