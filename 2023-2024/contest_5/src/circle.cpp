#include "../circle.h"
#include "../line.h"
#include "../point.h"
#include "../segment.h"
#include "../vector.h"

namespace geometry {

Circle Circle::operator=(const Circle &other) {
  if (this == &other) {
    return *this;
  }
  Circle tmp = other;
  Swap(*this, tmp);
  return *this;
}

Circle &Circle::Move(const Vector &v) {
  center_.Move(v);
  return *this;
}
bool Circle::ContainsPoint(const Point &p) const {
  return Point::Distance(center_, p) <= radius_;
}
bool Circle::CrossesSegment(const Segment &other) const {
  bool cp1 = ContainsPoint(other.GetPoint1());
  bool cp2 = ContainsPoint(other.GetPoint2());
  if (Point::Distance(center_, other.GetPoint1()) == radius_ ||
      Point::Distance(center_, other.GetPoint2()) == radius_) {
    return true;
  }
  if (cp1 && cp2)
    return false;
  if (cp1 || cp2)
    return true;
  return other.Distance(center_) <= radius_;
}
Circle *Circle::Clone() const {
  return new Circle(*this);
}
std::string Circle::ToString() const {
  std::string vars[]{center_.ToString(), std::to_string(radius_)};
  return StringFormat("Circle", vars, 2);
}

}  // namespace geometry