#include "polygon.h"
#include "segment.h"
#include "vector.h"
#include "point.h"
#include "line.h"

namespace geometry
{
  
Polygon Polygon::operator=(const Polygon& other){
  if (this == &other) { return *this; }
  Polygon tmp = other;
  Swap(*this, tmp);
  return *this;
}

void Polygon::Move(const Vector& v) {
  for (int i = 0; i < size_; i++) {
    vertices_[i].Move(v);
  }
}
bool Polygon::ContainsPoint(const Point& p) const {
  // TODO contains point polygon
  return true;
}
bool Polygon::CrossesSegment(const Segment &other) const {
  int res = 0;
  for (int i = 0; i < size_ - 1; i++) {
    res += Segment(vertices_[i], vertices_[i + 1]).CrossesSegment(other);
  }
  return res > 0;
}
Polygon* Polygon::Clone() const {
  return new Polygon(*this);
}
std::string Polygon::ToString() const {
  std::string points = "";
  if (size_) {
    for (int i = 0; i < size_ - 1; i++) {
      points += vertices_[i].ToString() + ", ";
    }
    points += vertices_[size_ - 1].ToString();
  }
  std::string vars[] { points };
  return StringFormat("Segment", vars, 1);
}

} // namespace geometry