#include "point.h"

#include "vector.h"

namespace geometry
{
  
void Point::Move(const Vector& v) {
  x_ += v.GetA();
  y_ += v.GetB();
}

} // namespace geometry