#include "ray.h"
#include "segment.h"
#include "vector.h"
#include "line.h"

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
bool Ray::ContainsPoint(const Point& p) const {
  Vector vp (p_, p);
  return Vector::AreColliniar(vp, v_);
}
bool Ray::CrossesSegment(const Segment& segment) const {
  if (segment.ContainsPoint(p_)) return true;
  
  Vector ao(segment.GetPoint1(), p_);
  return Vector::Cross(ao, GetVector()) * Vector::Cross(v_, GetVector()) < 0;
}
Ray* Ray::Clone() const {
  return new Ray(*this);
}
std::string Ray::ToString() const {
  std::string vars[] { p_.ToString(), v_.ToString() };
  return StringFormat("Ray", vars, 2);
}

double Ray::Distance(const Point& p) const {
  if (v_.GetLength() == 0) return Point::Distance(p, Point(v_.GetA(), v_.GetB()));

  Vector op(p_, p);
  if (Vector::Scalar(op, v_) > 0) return Vector::Cross(v_, op) / v_.GetLength();
  return op.GetLength();
}

Line Ray::GetLine() const {
  return Line(p_, v_);
}

bool Ray::IsParralel(const Ray& other) const {
  return GetVector() == other.GetVector();
}

bool Ray::ContainsSegment(const Segment& segment) const {
  return ContainsPoint(segment.GetPoint1()) && ContainsPoint(segment.GetPoint2());
}

} // namespace geometry