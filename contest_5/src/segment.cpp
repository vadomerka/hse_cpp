#include "../segment.h"
#include "../line.h"
#include "../point.h"
#include "../vector.h"

namespace geometry {

Segment Segment::operator=(const Segment &other) {
  if (this == &other) {
    return *this;
  }
  Segment tmp = other;
  Swap(*this, tmp);
  return *this;
}

Segment &Segment::Move(const Vector &v) {
  p1_.Move(v);
  p2_.Move(v);
  return *this;
}
bool Segment::ContainsPoint(const Point &p) const {
  Vector v1(p1_, p);
  Vector v2(p, p2_);
  return !Vector::Cross(v1, v2) && Vector::Scalar(v1, v2) >= 0;
}

bool CanIntersect(int x1, int x2, int x3, int x4) {
  int leftA = std::min(x1, x2);
  int rightA = std::max(x1, x2);
  int leftB = std::min(x3, x4);
  int rightB = std::max(x3, x4);
  return leftA < leftB ? (leftB <= rightA) : (leftA <= rightB);
}
bool CanIntersect(const geometry::Point &p1, const geometry::Point &p2, const geometry::Point &p3,
                  const geometry::Point &p4) {
  return CanIntersect(p1.GetX(), p2.GetX(), p3.GetX(), p4.GetX()) &&
         CanIntersect(p1.GetY(), p2.GetY(), p3.GetY(), p4.GetY());
}
bool Segment::CrossesSegment(const Segment &s) const {
  if (!CanIntersect(p1_, p2_, s.p1_, s.p2_)) {
    return false;
  }

  Vector v(p1_, p2_);
  Vector p1_a(p1_, s.p1_);
  Vector p1_b(p1_, s.p2_);

  int s1 = Sign(Vector::Cross(v, p1_a));
  int s2 = Sign(Vector::Cross(v, p1_b));

  v.Set(s.p1_, s.p2_);
  p1_a.Set(s.p1_, p1_);
  p1_b.Set(s.p1_, p2_);

  int s3 = Sign(Vector::Cross(v, p1_a));
  int s4 = Sign(Vector::Cross(v, p1_b));

  return (s1 != s2 && s3 != s4) || (!s1 && !s2 && !s3 && !s4);
}

Segment *Segment::Clone() const {
  return new Segment(*this);
}
std::string Segment::ToString() const {
  std::string vars[]{p1_.ToString(), p2_.ToString()};
  return StringFormat("Segment", vars, 2);
}

Line Segment::GetLine() const {
  return Line(p1_, Vector(p1_, p2_));
}

double Segment::Distance(const Point &p) const {
  if (GetLength() == 0)
    return Point::Distance(p1_, p);
  Vector ap(p1_, p);
  Vector ab(p1_, p2_);
  if (Vector::Scalar(ap, ab) <= 0)
    return ap.GetLength();
  Vector bp(p2_, p);
  Vector ba(p2_, p1_);
  if (Vector::Scalar(bp, ba) <= 0)
    return bp.GetLength();

  return Vector::Cross(ap, ab) / ap.GetLength();
}

}  // namespace geometry