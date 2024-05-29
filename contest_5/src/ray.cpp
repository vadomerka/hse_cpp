#include "../ray.h"
#include "../line.h"
#include "../segment.h"
#include "../vector.h"

namespace geometry {

Ray Ray::operator=(const Ray &other) {
  if (this == &other) {
    return *this;
  }
  Ray tmp = other;
  Swap(*this, tmp);
  return *this;
}

Ray &Ray::Move(const Vector &v) {
  p_.Move(v);
  return *this;
}
bool Ray::ContainsPoint(const Point &p) const {
  Vector vp(p_, p);
  return !Vector::Cross(vp, v_) && Vector::Scalar(vp, v_) >= 0;
}
bool Ray::CrossesSegment(const Segment &segment) const {
  if (segment.ContainsPoint(p_))
    return true;

  Vector oa(p_, segment.GetPoint1());
  Vector ob(p_, segment.GetPoint2());

  if (Vector::Scalar(v_, oa) < 0 && Vector::Scalar(v_, ob) < 0) {
    return false;
  }

  int s1 = Sign(Vector::Cross(v_, oa));
  int s2 = Sign(Vector::Cross(v_, ob));

  if (!s1 && !s2) {
    return true;
  } else if (s1 == s2) {
    return false;
  }

  Vector ao(segment.GetPoint1(), p_);
  Vector ab(segment.GetPoint1(), segment.GetPoint2());
  return Sign(Vector::Cross(ao, ob)) == Sign(Vector::Cross(ab, v_));
}
Ray *Ray::Clone() const {
  return new Ray(*this);
}
std::string Ray::ToString() const {
  std::string vars[]{p_.ToString(), v_.ToString()};
  return StringFormat("Ray", vars, 2);
}

double Ray::Distance(const Point &p) const {
  if (v_.GetLength() == 0)
    return Point::Distance(p, Point(v_.GetA(), v_.GetB()));

  Vector op(p_, p);
  if (Vector::Scalar(op, v_) > 0)
    return Vector::Cross(v_, op) / v_.GetLength();
  return op.GetLength();
}

Line Ray::GetLine() const {
  return Line(p_, v_);
}

bool Ray::IsParralel(const Ray &other) const {
  return GetVector() == other.GetVector();
}

bool Ray::ContainsSegment(const Segment &segment) const {
  return ContainsPoint(segment.GetPoint1()) && ContainsPoint(segment.GetPoint2());
}

}  // namespace geometry