#include "segment.h"
#include "vector.h"

namespace geometry
{
  
void Segment::Move(const Vector& v) {
  p1_.Move(v);
  p2_.Move(v);
}

} // namespace geometry