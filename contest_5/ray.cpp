#include "ray.h"
#include "segment.h"
#include "vector.h"

namespace geometry
{

Ray Ray::operator=(const Ray& other) {
  if (this == &other) { return *this; }
  Ray tmp = other;
  Swap(*this, tmp);
  return *this;
}

void Ray::Move(const Vector& v) {
  p_.Move(v);
}
bool Ray::ContainsPoint(const Point& p) {
  Vector vp (p_, p);
  return Vector::IsColliniar(vp, v_);
}
bool Ray::CrossesSegment(const Segment& segment) {
  return true;// PointPlane(segment.GetPoint1(), segment.GetPoint2());
}
Ray* Ray::Clone() {
  return new Ray(*this);
}
std::string Ray::ToString() {
  std::string vars[] { p_.ToString(), v_.ToString() };
  return StringFormat("Ray", vars, 3);
}

double Ray::Distance(const Point& p) const {  // TODO ray
  Vector op(p_, p);
  if (Vector::Scalar(op, v_) > 0) return 0;
  return 0.0;
}

bool Ray::IsParralel(const Ray& other) const {
  return GetVector() == other.GetVector();
}


} // namespace geometry